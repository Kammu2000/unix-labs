import { createReadStream } from "fs";
import { StringDecoder } from "string_decoder";

export interface WcResult {
  lines: number;
  bytes: number;
  words: number;
}

const getNewLineCharCnt = (chunkStr: string): number => {
  let result = 0;

  for (const ch of chunkStr) {
    if (ch === "\n") {
      result++;
    }
  }

  return result;
};

export const wc = async (filePath: string): Promise<WcResult> => {
  const decoder = new StringDecoder("utf8");

  let lineCnt = 0,
    byteCnt = 0,
    wordCnt = 0;
  let leftOverChunk = "";

  const stream = createReadStream(filePath);

  for await (const chunk of stream) {
    const chunkStr = decoder.write(chunk);

    byteCnt += chunk.length;
    lineCnt += getNewLineCharCnt(chunkStr);

    const adaptedChunkStr = leftOverChunk + chunkStr;
    const words = adaptedChunkStr.split(/\s+/);

    leftOverChunk = words.pop() ?? "";
    wordCnt += words.length;
  }

  const tail = decoder.end();

  if (tail) {
    lineCnt += getNewLineCharCnt(tail);

    const adaptedChunkStr = leftOverChunk + tail;
    const words = adaptedChunkStr.split(/\s+/);

    leftOverChunk = words.pop() ?? "";
    wordCnt += words.length;
  }

  if (leftOverChunk) {
    wordCnt++;
  }

  return { lines: lineCnt, bytes: byteCnt, words: wordCnt };
};
