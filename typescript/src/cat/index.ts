import { existsSync } from "fs";
import path from "path";
import yargs from "yargs";
import { hideBin } from "yargs/helpers";
import { myCatNaive } from "./naive.js";
import { myCatStreaming } from "./streaming.js";
import { myCatIdiomatic } from "./idiomatic.js";

const argv = yargs(hideBin(process.argv))
  .option("files", {
    alias: "f",
    type: "string",
    array: true,
    demandOption: true,
  })
  .parseSync();

process.stdout.on("error", (err: NodeJS.ErrnoException) => {
  // Rationale: consumer which was consuming stream data exited and we don't destroy stream (so we keep writing to destroyed consumer)
  // then we get EPIPE error
  if (err.code === "EPIPE") {
    process.exit(0);
  } else {
    throw err;
  }
});

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
