import { createReadStream, existsSync } from "fs";
import path from "path";
import yargs from "yargs";
import { hideBin } from "yargs/helpers";
import { head } from "./head";

const argv = yargs(hideBin(process.argv))
  .option("files", {
    alias: "f",
    type: "string",
    array: true,
    demandOption: true,
  })
  .option("count", {
    alias: "n",
    type: "number",
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

const { files, count } = argv;

for (const file of files) {
  const filePath = path.resolve(file);

  if (existsSync(filePath)) {
    const stream = createReadStream(filePath);
    head(stream, count);
  } else {
    process.stderr.write("No such file exists \n");
  }
}
