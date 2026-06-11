import path from "path";
import { readdirSync, statSync } from "fs";
import { EntityInfo, EntityType, Filter } from "./filters.js";

const isValidEntity = (entity: EntityInfo, filters: Filter[]): boolean => {
  return filters.every((filter) => filter(entity));
};

export const walk = (
  entityPath: string,
  filters: Filter[],
  rootPath: string,
): number => {
  const entries = readdirSync(entityPath);
  let totalSize = 0;

  for (const entry of entries) {
    const entryPath = path.join(entityPath, entry);
    const stats = statSync(entryPath);

    if (stats.isFile()) {
      const fileInfo: EntityInfo = {
        name: path.basename(entryPath),
        type: EntityType.FILE,
        path: entryPath,
        size: stats.size,
      };

      if (isValidEntity(fileInfo, filters)) {
        const displayPath = path.relative(rootPath, entryPath);
        process.stdout.write(`${displayPath}\n`);
      }

      totalSize += fileInfo.size;
    } else if (stats.isDirectory()) {
      totalSize += walk(entryPath, filters, rootPath);
    }
  }

  const entityInfo: EntityInfo = {
    name: path.basename(entityPath),
    type: EntityType.DIRECTORY,
    path: entityPath,
    size: 0,
  };

  entityInfo.size = totalSize;

  const displayPath = path.relative(rootPath, entityPath);

  if (isValidEntity(entityInfo, filters)) {
    process.stdout.write(`${displayPath}\n`);
  }

  return entityInfo.size;
};

export const find = (startPath: string, filters: Filter[]): void => {
  /* Learning Notes: gives absolute by joining process.cwd and startPath. if startPath is already absolute then it returns it unchanged
   path.join("/Users/deepanshu/project", "../other");
   gives:
   /Users/deepanshu/project/../other
   while
   path.resolve("../other");
   gives:
   /Users/deepanshu/other
  */

  const root = path.resolve(startPath);
  walk(root, filters, root);
};
