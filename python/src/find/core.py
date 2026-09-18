from pathlib import Path
from dataclasses import dataclass
from enum import Enum


class EntityType(Enum):
    FILE = "f"
    DIRECTORY = "d"


@dataclass
class EntityInfo:
    name: str
    type: EntityType
    path: str


def is_valid_entity(entity_info: EntityInfo, filters) -> bool:
    return all(filter(entity_info) for filter in filters)


def find(search_path, filters):
    search_path_dir = Path(search_path)

    for entity in search_path_dir.rglob("*"):
        entity_info = EntityInfo(
            name=entity.name,
            type=EntityType.FILE if entity.is_file() else EntityType.DIRECTORY,
            path=str(entity),
        )

        if is_valid_entity(entity_info, filters=filters):
            print(f"./{entity_info.path}" if search_path == "." else entity_info.path)
