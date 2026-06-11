import { existsSync } from "fs";
import path from "path";
import yargs from "yargs";
import { hideBin } from "yargs/helpers";
import { wc, WcResult } from "./wc.js";
// import { wc as wc2 } from "./wc2";

const argv = yargs(hideBin(process.argv))
  .option("files", {
    alias: "f",
    type: "string",
    array: true,
    demandOption: true,
  })
  .parseSync();

const files = argv.files;

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
    // Approach-1:
    // wc2(filePath).then((result: WcResult): void => {
    //   const { lines, words, bytes } = result;
    //   process.stdout.write(
    //     `lines: ${lines}, words: ${words}, bytes: ${bytes}, file: ${file}\n`,
    //   );
    // });

    // Approach-2:
    wc(filePath).then((result: WcResult): void => {
      const { lines, words, bytes } = result;
      process.stdout.write(
        `lines: ${lines}, words: ${words}, bytes: ${bytes}, file: ${file}\n`,
      );
    });
  } else {
    process.stderr.write("No such file exists \n");
  }
}
