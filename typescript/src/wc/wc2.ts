import { createReadStream } from "fs";
import { StringDecoder } from "string_decoder";

export interface WcResult {
  lines: number;
  bytes: number;
  words: number;
}

const WHITESPACE = " \n\t\r\f\v";

const isWhitespace = (ch: string): boolean => {
  return WHITESPACE.includes(ch);
};

export const wc = async (filePath: string): Promise<WcResult> => {
  const decoder = new StringDecoder("utf8");

  let lineCnt = 0;
  let byteCnt = 0;
  let wordCnt = 0;

  let inWord = false;

  const stream = createReadStream(filePath);

  const handleChunksStr = (chunkStr: string): void => {
    for (const ch of chunkStr) {
      if (ch === "\n") {
        lineCnt++;
      }

      if (isWhitespace(ch)) {
        inWord = false;
      } else if (!inWord) {
        wordCnt++;
        inWord = true;
      }
    }
  };

  for await (const chunk of stream) {
    const chunkStr = decoder.write(chunk);

    byteCnt += chunk.length;
    handleChunksStr(chunkStr);
  }

  const tail = decoder.end();

  if (tail) {
    byteCnt += Buffer.byteLength(tail);
    handleChunksStr(tail);
  }

  return {
    lines: lineCnt,
    bytes: byteCnt,
    words: wordCnt,
  };
};
