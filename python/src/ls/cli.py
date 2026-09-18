import argparse
from src.ls.core import ls


def main():
    parser = argparse.ArgumentParser(description="grep.py")

    parser.add_argument(
        "-a",
        action="store_true",
        help="flag for printing hidden files",
    )
    parser.add_argument(
        "dirs",
        nargs="*",
        default=["."],
        help="directories to list",
    )

    args = parser.parse_args()

    for directory in args.dirs:
        if len(args.dirs) > 1:
            print(f"{directory}: ")
        ls(directory=directory, flags=[args.a])
        print("\n")


if __name__ == "__main__":
    main()
