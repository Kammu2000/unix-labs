import { spawn } from "child_process";
import { StringDecoder } from "string_decoder";

const command = process.argv[2];

if (!command) {
  process.stderr.write("No command was provided in xargs");
}

const decoder = new StringDecoder("utf8");

let input = "";

for await (const chunk of process.stdin) {
  input += decoder.write(chunk);
}

input += decoder.end();

const args = input.trim().split(/\s+/).filter(Boolean);

const child = spawn(command, [...process.argv.slice(3), ...args], {
  stdio: "inherit",
});

child.on("error", (err: Error): void => {
  process.stderr.write(err.message);
  process.exit(1);
});

child.on("exit", (code: number): void => {
  process.exit(code ?? 1);
});
