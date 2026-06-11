import { cpus } from "os";
import path from "path";
import { GrepRes, GrepReq } from "./types.js";
import { WorkerPool } from "../common/worker-pool.js";
import { logMatch } from "./grep_v1.js";

const workerScriptUrl = new URL("./grep-worker.js", import.meta.url);

export const grep_v2 = async (
  pattern: string,
  files: string[],
): Promise<void> => {
  const workerPool = new WorkerPool<GrepReq, GrepRes>({
    size: cpus().length / 2,
    workerScript: workerScriptUrl,
  });

  const tasksPromises = files.map((file: string): Promise<GrepRes> => {
    const filePath = path.resolve(file);
    return workerPool.submitTask({ filePath, pattern });
  });

  try {
    const results = await Promise.all(tasksPromises);

    results.forEach((res: GrepRes) => {
      res.matches.forEach((match: string) => logMatch(res.filePath, match));
    });
  } catch (err: any) {
    process.stderr.write(`${err.message ?? "unknown error occured"}`);
  } finally {
    await workerPool.destroy();
  }
};
