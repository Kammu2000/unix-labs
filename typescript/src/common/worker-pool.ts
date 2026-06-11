import { Worker } from "worker_threads";

export enum MessageType {
  TASK = "TASK",
  RESULT = "RESULT",
  ERROR = "ERROR",
}

export type TaskId = number;

export interface TaskMessage<T> {
  type: MessageType.TASK;
  taskId: TaskId;
  payload: T;
}

export interface ResultMessage<T> {
  type: MessageType.RESULT;
  taskId: TaskId;
  payload: T;
}

export interface ErrorMessage<T> {
  type: MessageType.ERROR;
  taskId: TaskId;
  payload: T;
}

export class WorkerPool<TReq, TRes> {
  private poolSize: number;
  private workerScript: URL;
  private workers: Worker[] = [];
  private idleWorkers: Worker[] = [];
  private taskQueue: TaskMessage<TReq>[] = [];
  private pendingTasks = new Map<
    TaskId,
    { resolve: (value: TRes) => void; reject: (err: Error) => void }
  >();
  private taskCounter = 0;

  constructor({ size, workerScript }: { size: number; workerScript: URL }) {
    this.poolSize = size;
    this.workerScript = workerScript;

    for (let i = 0; i < this.poolSize; i++) {
      const worker = this.createWorker();
      this.workers.push(worker);
      this.idleWorkers.push(worker);
    }
  }

  private createWorker(): Worker {
    const worker = new Worker(this.workerScript);

    worker.on(
      "message",
      (msg: ResultMessage<TRes> | ErrorMessage<string>): void => {
        this.onWorkerMessage(worker, msg);
      },
    );

    worker.on("error", (err: Error): void => {
      process.stderr.write(`${err.message}\n`);
    });
    return worker;
  }

  private onWorkerMessage(
    worker: Worker,
    msg: ResultMessage<TRes> | ErrorMessage<string>,
  ): void {
    const taskHandlers = this.pendingTasks.get(msg.taskId);

    if (!taskHandlers) {
      return;
    }

    this.pendingTasks.delete(msg.taskId);
    this.idleWorkers.push(worker);

    if (msg.type === MessageType.ERROR) {
      taskHandlers.reject(new Error(msg.payload));
    } else {
      taskHandlers.resolve(msg.payload);
    }

    this.processNextTask();
  }

  private processNextTask(): void {
    if (this.taskQueue.length === 0 || this.idleWorkers.length === 0) {
      return;
    }

    const task = this.taskQueue.shift();

    if (this.idleWorkers.length > 0) {
      const worker = this.idleWorkers.pop() as Worker;
      worker.postMessage(task);
    }
  }

  submitTask(task: TReq): Promise<TRes> {
    return new Promise((resolve, reject) => {
      const taskId = this.taskCounter++;
      this.pendingTasks.set(taskId, { resolve, reject });

      const taskMessage: TaskMessage<TReq> = {
        type: MessageType.TASK,
        taskId,
        payload: task,
      };

      this.taskQueue.push(taskMessage);
      this.processNextTask();
    });
  }

  async destroy(): Promise<void> {
    await Promise.all(this.workers.map((worker) => worker.terminate()));
  }
}
