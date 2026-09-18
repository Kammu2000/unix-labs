from pathlib import Path


def is_hidden(name: str) -> bool:
    return len(name) > 0 and name[0] == "."


def ls(directory: str, flags: list[bool]) -> None:
    [show_hidden_files] = flags
    dir_path = Path(directory)

    for entity in sorted(dir_path.iterdir()):
        if is_hidden(entity.name) and not show_hidden_files:
            continue
        print(entity.name, end="\t")

    return
