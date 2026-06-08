import { existsSync } from "fs";
import path from "path";
import yargs from "yargs";
import { hideBin } from "yargs/helpers";
import { grep_v1 } from "./grep_v1";

const argv = yargs(hideBin(process.argv))
  .option("files", {
    alias: "f",
    type: "string",
    array: true,
    demandOption: true,
  })
  .option("pattern", {
    alias: "p",
    type: "string",
    demandOption: true,
  })
  .parseSync();

const { files, pattern } = argv;

process.stdout.on("error", (err: NodeJS.ErrnoException) => {
  // Rationale: consumer which was consuming stream data exited and we don't destroy stream (so we keep writing to destroyed consumer)
  // then we get EPIPE error
  if (err.code === "EPIPE") {
    process.exit(0);
  } else {
    throw err;
  }
});

for (const file of files) {
  const filePath = path.resolve(file);

  if (existsSync(filePath)) {
    grep_v1(pattern, filePath);
  } else {
    process.stderr.write("No such file exists \n");
  }
}
