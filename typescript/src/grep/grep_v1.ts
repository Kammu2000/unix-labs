import { createReadStream } from "fs";
import path from "path";
import { StringDecoder } from "string_decoder";

export const grep_v1 = async (
  pattern: string,
  filePath: string,
): Promise<void> => {
  const relativeFilePath = path.relative(process.cwd(), filePath);
  const decoder = new StringDecoder("utf8");
  const stream = createReadStream(filePath);

  let line = "";

  const processChunk = (chunkStr: string) => {
    for (const ch of chunkStr) {
      if (ch === "\n") {
        if (line.includes(pattern)) {
          process.stdout.write(`${relativeFilePath}:${line}\n`);
        }

        line = "";
      } else {
        line += ch;
      }
    }
  };

  for await (const chunk of stream) {
    const chunkStr = decoder.write(chunk);
    processChunk(chunkStr);
  }

  const remainingChunk = decoder.end();
  processChunk(remainingChunk);
};
