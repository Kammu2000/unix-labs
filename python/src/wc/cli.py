import argparse
import sys
from src.wc.core import wc


def main():
    parser = argparse.ArgumentParser(description="wc.py")

    parser.add_argument(
        "-l",
        "--lines",
        required=False,
        action="store_true",
        help="Flag to confirm if count of lines should be printed",
    )
    parser.add_argument(
        "-w",
        "--words",
        required=False,
        action="store_true",
        help="Flag to confirm if count of lines should be printed",
    )
    parser.add_argument(
        "-m",
        "--characters",
        required=False,
        action="store_true",
        help="Flag to confirm if count of lines should be printed",
    )
    parser.add_argument(
        "-c",
        "--bytes",
        required=False,
        action="store_true",
        help="Flag to confirm if count of lines should be printed",
    )
    parser.add_argument(
        "filename",
        nargs="?",
        default=None,
        help="Input file path (defaults to standard input if omitted)",
    )

    args = parser.parse_args()

    file_buffer = open(args.filename, "rb") if args.filename else sys.stdin.buffer
    lines_count, words_count, characters_count, bytes_count = wc(file_buffer)

    if not args.lines and not args.words and not args.characters and not args.bytes:
        print(
            f"{lines_count} {words_count} {characters_count} {bytes_count} {args.filename}"
        )
    elif args.lines:
        print(f"{lines_count} {args.filename}")
    elif args.words:
        print(f"{words_count} {args.filename}")
    elif args.characters:
        print(f"{characters_count} {args.filename}")
    elif args.bytes:
        print(f"{bytes_count} {args.filename}")


if __name__ == "__main__":
    main()
