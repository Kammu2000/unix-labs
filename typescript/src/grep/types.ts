export interface GrepReq {
  filePath: string;
  pattern: string;
}

export interface GrepRes {
  filePath: string;
  matches: string[];
}
