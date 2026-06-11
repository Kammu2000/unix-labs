import { parentPort } from "worker_threads";
import { MessageType, TaskMessage } from "../common/worker-pool.js";
import { grep } from "./grep_v1.js";
import { GrepReq } from "./types.js";

parentPort?.on("message", async (msg: TaskMessage<GrepReq>): Promise<void> => {
  try {
    const result = await grep(msg.payload.pattern, msg.payload.filePath);

    parentPort?.postMessage({
      type: MessageType.RESULT,
      taskId: msg.taskId,
      payload: result,
    });
  } catch (err) {
    parentPort?.postMessage({
      type: MessageType.ERROR,
      taskId: msg.taskId,
      payload: String(err),
    });
  }
});
