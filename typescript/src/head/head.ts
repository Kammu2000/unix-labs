import { Readable } from "stream";
import { StringDecoder } from "string_decoder";

export const head = async (stream: Readable, cnt: number): Promise<void> => {
  const decoder = new StringDecoder("utf8");
  let lineCnt = 0;
  let leftOverChunk = "";

  for await (const chunk of stream) {
    const chunkStr = leftOverChunk + decoder.write(chunk);
    const lines = chunkStr.split("\n");
    leftOverChunk = lines.pop() ?? "";

    for (const line of lines) {
      if (lineCnt >= cnt) {
        stream.destroy();
        return;
      }

      process.stdout.write(`${line}\n`);
      lineCnt++;
    }
  }

  if (lineCnt < cnt && leftOverChunk) {
    process.stdout.write(`${leftOverChunk}\n`);
  }
};
