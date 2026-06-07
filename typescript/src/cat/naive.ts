import { readFileSync } from "fs";

export const myCatNaive = (filePath: string): void => {
  const fileContent = readFileSync(filePath);
  process.stdout.write(`${fileContent}\n`);
};
