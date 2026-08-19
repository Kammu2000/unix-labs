import argparse
import sys
from itertools import islice


def main():
    parser = argparse.ArgumentParser(description="head.py")

    parser.add_argument(
        "-n",
        "--lines",
        type=int,
        required=False,
        default=10,
        help="Number of lines to be printed",
    )
    parser.add_argument(
        "filename",
        nargs="?",
        default=None,
        help="Input file path (defaults to standard input if omitted)",
    )

    args = parser.parse_args()

    f = open(args.filename, "r") if args.filename else sys.stdin

    for line in islice(f, args.lines):
        print(line, end="")


if __name__ == "__main__":
    main()
