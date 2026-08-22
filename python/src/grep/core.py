from typing import Iterable


def grep(pattern: str, content: Iterable[str]) -> None:
    for idx, line in enumerate(content):
        if pattern in line:
            print(f"{idx}:  {line}", end="")
