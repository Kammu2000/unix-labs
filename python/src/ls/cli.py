import argparse
from src.ls.core import ls


def main():
    parser = argparse.ArgumentParser(description="grep.py")

    parser.add_argument(
        "-l",
        action="store_true",
        help="flag for printing files in long list format",
    )
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
        print(directory, end="")
        ls(directory=directory, flags=[args.l, args.a])


if __name__ == "__main__":
    main()
