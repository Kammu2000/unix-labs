import argparse
from fnmatch import fnmatchcase
from src.find.core import find


def name_filter(pattern):
    return lambda entity: fnmatchcase(entity.name, pattern)


def type_filter(entity_type):
    return lambda entity: entity.type == entity_type


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("search_path")
    parser.add_argument("-name", required=False, help="Match filename")
    parser.add_argument(
        "-type",
        choices=["f", "d"],
        help="File type: f=file, d=directory",
    )

    args = parser.parse_args()
    filters = []

    if args.name:
        filters.append(name_filter(args.name))

    if args.type:
        filters.append(type_filter(args.type))

    find(args.search_path, filters)


if __name__ == "__main__":
    main()
