import argparse
import sys
from constants import BUFFER_SIZE


def main():
    parser = argparse.ArgumentParser(description="cat.py")

    parser.add_argument(
        "filename",
        nargs="?",
        default=None,
        help="Input file path (defaults to standard input if omitted)",
    )

    args = parser.parse_args()

    f = open(args.filename, "rb") if args.filename else sys.stdin.buffer

    while chunk := f.read(BUFFER_SIZE):
        sys.stdout.buffer.write(chunk)


if __name__ == "__main__":
    main()
