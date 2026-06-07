import { createReadStream } from "fs";

export const myCatStreaming = (filePath: string): void => {
  const stream = createReadStream(filePath);

  stream.on("data", (chunk: Buffer) => {
    process.stdout.write(chunk.toString());
  });

  process.stdout.on("error", (err: NodeJS.ErrnoException) => {
    // Rationale: consumer which was consuming stream data exited and we don't destroy stream (so we keep writing to destroyed consumer)
    // then we get EPIPE error
    if (err.code === "EPIPE") {
      stream.destroy();
      return;
    }

    throw err;
  });
};
