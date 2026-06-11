import { createReadStream } from "fs";
import path from "path";
import { StringDecoder } from "string_decoder";
import { GrepRes } from "./types.js";

export const grep = async (
  pattern: string,
  filePath: string,
): Promise<GrepRes> => {
  const relativeFilePath = path.relative(process.cwd(), filePath);
  const decoder = new StringDecoder("utf8");
  const stream = createReadStream(filePath);
  const matches: string[] = [];

  let line = "";

  const processChunk = (chunkStr: string) => {
    for (const ch of chunkStr) {
      if (ch === "\n") {
        if (line.includes(pattern)) {
          matches.push(line);
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

  return { filePath: relativeFilePath, matches };
};

export const logMatch = (filePath: string, match: string): void => {
  process.stdout.write(`${filePath}:${match}\n`);
};

export const grep_v1 = async (
  pattern: string,
  files: string[],
): Promise<void> => {
  const tasksPromises = files.map((file: string): Promise<GrepRes> => {
    const filePath = path.resolve(file);
    return grep(pattern, filePath);
  });

  const results = await Promise.all(tasksPromises);

  results.forEach((res: GrepRes): void => {
    res.matches.forEach((match: string): void => {
      logMatch(res.filePath, match);
    });
  });
};
