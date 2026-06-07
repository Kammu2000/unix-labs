import { createReadStream } from "fs";

export const myCatIdiomatic = (filePath: string): void => {
  const stream = createReadStream(filePath);
  stream.pipe(process.stdout);
};
