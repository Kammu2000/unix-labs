import argparse
import sys
from src.grep.core import grep


def main():
    parser = argparse.ArgumentParser(description="grep.py")

    parser.add_argument("pattern", help="pattern which needs to be searched")
    parser.add_argument(
        "filename",
        nargs="?",
        default=None,
        help="Input file path (defaults to standard input if omitted)",
    )

    args = parser.parse_args()

    filename = open(args.filename, "r") if args.filename else sys.stdin
    grep(args.pattern, filename)


if __name__ == "__main__":
    main()
