import { createReadStream } from "fs";
import { StringDecoder } from "string_decoder";

export const myCatStreaming = async (filePath: string): Promise<void> => {
  const stream = createReadStream(filePath);
  const decoder = new StringDecoder("utf8");

  for await (const chunk of stream) {
    const chunkStr = decoder.write(chunk);
    process.stdout.write(chunkStr);
  }
};
