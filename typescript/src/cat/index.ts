import { existsSync } from "fs";
import path from "path";
import yargs from "yargs";
import { hideBin } from "yargs/helpers";
import { myCatNaive } from "./naive";
import { myCatStreaming } from "./streaming";
import { myCatIdiomatic } from "./idiomatic";

const argv = yargs(hideBin(process.argv))
  .option("files", {
    alias: "f",
    type: "string",
    array: true,
    demandOption: true,
  })
  .parseSync();

const files = argv.files;

for (const file of files) {
  const filePath = path.resolve(file);

  if (existsSync(filePath)) {
    myCatNaive(filePath);
    myCatStreaming(filePath);
    myCatIdiomatic(filePath);
  } else {
    process.stderr.write("No such file exists \n");
  }
}
