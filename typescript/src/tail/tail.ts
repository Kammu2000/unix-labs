import { Readable } from "stream";
import { StringDecoder } from "string_decoder";

export const tail = async (stream: Readable, count: number): Promise<void> => {
  const decoder = new StringDecoder("utf8");
  let lines: string[] = [];
  let buffer = "";

  const processChunk = (chunkStr: string) => {
    for (const ch of chunkStr) {
      if (ch === "\n") {
        lines.push(buffer);
        buffer = "";

        if (lines.length > count) {
          lines.shift();
        }
      } else buffer += ch;
    }
  };

  for await (const chunk of stream) {
    const chunkStr = decoder.write(chunk);
    processChunk(chunkStr);
  }

  const remainingChunk = decoder.end();
  processChunk(remainingChunk);

  for (const line of lines) {
    process.stdout.write(`${line}\n`);
  }
};
