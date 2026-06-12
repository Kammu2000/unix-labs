import path from "path";
import { readdirSync, statSync } from "fs";
import { humanReadableSize } from "./utils.js";

export interface DuOptions {
  humanReadable: boolean;
  showFiles: boolean;
  showTotal: boolean;
}

const logEntity = (
  entitySize: number,
  displayPath: string,
  humanReadable: boolean,
): void => {
  const displaySize = humanReadable
    ? humanReadableSize(entitySize)
    : entitySize;
  process.stdout.write(`${displaySize}  ${displayPath} \n`);
};


/*
 * Design Decision: Using `stats.size` (logical file size) instead of `stats.blocks`.
 *
 * GNU `du` reports disk usage, which is based on allocated filesystem blocks.
 * POSIX exposes this via `stats.blocks`, where each block is reported in
 * units of 512 bytes. Actual filesystem blocks are often larger (e.g. 4 KB),
 * but the kernel normalizes the value to 512-byte units.
 *
 * Example:
 *   File contents: 1700 bytes
 *   stats.size   => 1700
 *   stats.blocks => 32
 *
 * Disk usage reported by GNU du:
 *   32 * 512 = 16384 bytes (16 KB)
 *
 * This implementation intentionally reports logical file size because it is
 * simpler and more intuitive for learning purposes.
 */

const walk = (entityPath: string, options: DuOptions): number => {
  const entityStats = statSync(entityPath);
  const displayPath = path.relative(process.cwd(), entityPath);

  if (entityStats.isFile()) {
    if (options.showFiles) {
      logEntity(entityStats.size, displayPath, options.humanReadable);
    }

    return entityStats.size;
  }

  const entries = readdirSync(entityPath);
  let totalSize = 0;

  for (const entry of entries) {
    const entryPath = path.join(entityPath, entry);
    totalSize += walk(entryPath, options);
  }

  logEntity(totalSize, displayPath, options.humanReadable);
  return totalSize;
};

export const du = (startPath: string, options: DuOptions): void => {
  const rootPath = path.resolve(startPath);
  const grandTotal = walk(rootPath, options);

  if (options.showTotal) {
    const total = options.humanReadable
      ? humanReadableSize(grandTotal)
      : grandTotal;
    process.stdout.write(`${total}  total \n`);
  }
};
