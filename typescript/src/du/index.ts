import yargs from "yargs";
import { hideBin } from "yargs/helpers";
import { du } from "./du.js";

const { dir, humanReadable, showFiles, showTotal } = yargs(
  hideBin(process.argv),
)
  .option("dir", {
    alias: "d",
    type: "string",
    default: process.cwd(),
  })
  .option("humanReadable", {
    alias: "h",
    type: "boolean",
    default: false,
  })
  .option("showFiles", {
    alias: "a",
    type: "boolean",
    default: false,
  })
  .option("showTotal", {
    alias: "c",
    type: "boolean",
    default: false,
  })
  .parseSync();

du(dir, { humanReadable, showFiles, showTotal });
