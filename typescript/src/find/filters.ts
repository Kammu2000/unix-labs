import { minimatch } from "minimatch";

export enum EntityType {
  FILE = "FILE",
  DIRECTORY = "DIRECTORY",
}

export interface EntityInfo {
  name: string;
  path: string; // relative to current working dir
  type: EntityType;
  size: number;
}

export type Filter = (entity: EntityInfo) => boolean;

export const nameFilter =
  (pattern: string): Filter =>
  (entity) =>
    minimatch(entity.name, pattern);

export const typeFilter =
  (type: EntityType): Filter =>
  (entity) =>
    entity.type === type;

export const sizeFilter =
  (size: number): Filter =>
  (entity) =>
    entity.size > size;
