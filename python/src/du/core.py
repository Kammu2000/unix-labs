from dataclasses import dataclass
from pathlib import Path


@dataclass
class Args:
    show_all: bool
    human_readable: bool


def get_human_readable_size(entity_size: float) -> str:
    size_prefix = ["B", "K", "M", "G", "T"]
    i = 0

    while entity_size >= 1024 and i < len(size_prefix) - 1:
        entity_size /= 1024
        i += 1

    return f"{entity_size:.1f}{size_prefix[i]}"


def log_entity(entity_size: int, entity_name: str, human_readable: bool) -> None:
    size = get_human_readable_size(entity_size) if human_readable else entity_size
    print(f"{size}\t{entity_name}")


def walk(dir_path: Path, args: Args) -> int:
    total_size = 0

    for entity in dir_path.iterdir():
        if entity.is_file():
            file_size = entity.stat().st_size
            total_size += file_size

            if args.show_all:
                log_entity(
                    file_size,
                    str(entity.relative_to(Path.cwd())),
                    args.human_readable,
                )

        elif entity.is_dir():
            dir_size = walk(entity, args)
            total_size += dir_size

            log_entity(
                dir_size,
                str(entity.relative_to(Path.cwd())),
                args.human_readable,
            )

    return total_size


def du(dir_path: str, args: Args) -> None:
    path = Path(dir_path).resolve()
    total_size = walk(path, args)

    log_entity(
        total_size,
        entity_name=str(path.relative_to(Path.cwd())),
        human_readable=args.human_readable,
    )
