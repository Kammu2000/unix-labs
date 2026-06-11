import path from "path";
import { existsSync, readdirSync } from "fs";
import yargs from "yargs";
import { hideBin } from "yargs/helpers";
import { grep_v1 } from "./grep_v1.js";
// import { grep_v2 } from "./grep_v2.js";

const argv = yargs(hideBin(process.argv))
  .option("files", {
    alias: "f",
    type: "string",
    array: true,
  })
  .option("dir", {
    alias: "d",
    type: "string",
  })
  .option("pattern", {
    alias: "p",
    type: "string",
    demandOption: true,
  })
  .check((argv) => {
    if (!argv.files && !argv.dir) {
      throw new Error("Either --files (-f) or --dir (-d) must be provided");
    }

    return true;
  })
  .parseSync();

const { files = [], dir, pattern } = argv;

process.stdout.on("error", (err: NodeJS.ErrnoException) => {
  // Rationale: consumer which was consuming stream data exited and we don't destroy stream (so we keep writing to destroyed consumer)
  // then we get EPIPE error
  if (err.code === "EPIPE") {
    process.exit(0);
  } else {
    throw err;
  }
});

try {
  if (dir && existsSync(dir)) {
    const dirPath = path.resolve(dir);
    const entries = readdirSync(dirPath, {
      recursive: true,
      withFileTypes: true,
    });

    const dirFiles = entries
      .filter((entry) => entry.isFile())
      .map((entry) => path.join(entry.parentPath, entry.name));

    files.push(...dirFiles);
  }

  await grep_v1(pattern, files);
} catch (err: any) {
  process.stderr.write(err);
}
