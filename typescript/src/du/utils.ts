export const humanReadableSize = (bytes: number): string => {
  const units = ["B", "K", "M", "G", "T"];
  let i = 0;

  while (bytes >= 1024 && i < units.length - 1) {
    bytes /= 1024;
    i++;
  }

  return `${bytes.toFixed(1)}${units[i]}`;
};
