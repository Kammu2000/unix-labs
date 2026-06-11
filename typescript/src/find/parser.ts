import {
  EntityType,
  Filter,
  nameFilter,
  sizeFilter,
  typeFilter,
} from "./filters.js";

export interface ParsedFind {
  startPath: string;
  filters: Filter[];
}

export const parseFind = (): ParsedFind => {
  const args = process.argv.slice(2);
  const expressions: string[] = [];
  let startPath = "";

  for (let idx = 0; idx < args.length; idx++) {
    const arg = args[idx];

    if (idx === 0 && !arg.startsWith("-")) {
      startPath = arg;
    } else {
      expressions.push(arg);
    }
  }

  const filters: Filter[] = [];

  for (let idx = 0; idx < expressions.length - 1; idx++) {
    const token = expressions[idx];

    switch (token) {
      case "-name": {
        filters.push(nameFilter(expressions[++idx]));
        break;
      }

      case "-type": {
        const typeToken = expressions[++idx];

        if (typeToken === "f" || typeToken === "d") {
          const entityType =
            typeToken === "f" ? EntityType.FILE : EntityType.DIRECTORY;
          filters.push(typeFilter(entityType));
        } else {
          throw new Error(`Invalid entityType flag: ${typeToken}`);
        }
        break;
      }

      case "-size": {
        const size = Number(expressions[++idx]);

        if (Number.isFinite(size)) {
          filters.push(sizeFilter(size));
        } else {
          throw new Error("Size is not a number");
        }

        break;
      }
    }
  }

  return { startPath, filters };
};
