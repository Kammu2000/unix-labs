import argparse
from src.du.core import du, Args


def main():
    parser = argparse.ArgumentParser()
    parser = argparse.ArgumentParser(add_help=False)

    parser.add_argument("-a", action="store_true", help="show all (files and folders)")
    parser.add_argument(
        "-h",
        action="store_true",
        help="human readable sizes of displayed filesystem entities",
    )
    parser.add_argument("--help", action="help")
    parser.add_argument("dirs", nargs="*", default=["."])

    args = parser.parse_args()

    for dir in args.dirs:
        du(dir, Args(args.a, args.h))


if __name__ == "__main__":
    main()
