import argparse
import sys
from collections import deque


def main():
    parser = argparse.ArgumentParser(description="tail.py")

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
    q = deque()

    for line in f:
        q.append(line)

        if len(q) > args.lines:
            q.popleft()

    while len(q) > 0:
        print(q.popleft(), end="")


if __name__ == "__main__":
    main()
