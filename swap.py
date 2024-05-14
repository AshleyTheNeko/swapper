#!/usr/bin/env python3
from sys import argv
from typing import List


def find_combos(words: List[str]) -> List[List[str]]:
    if len(words) <= 1:
        return [words]
    if len(words) == 2:
        return [[words[0], words[1]], [words[1], words[0]]]

    words_copy = words.copy()
    all_combos: List[List[str]] = []
    for _ in range(0, len(words_copy)):
        new_combos = find_combos(words_copy[1:])
        for i in range(0, len(new_combos)):
            new_combos[i].insert(0, words_copy[0])
        all_combos += new_combos
        last = words_copy.pop()
        words_copy.insert(0, last)

    return all_combos


def main() -> int:
    if len(argv) <= 1:
        print("At least pass one arg")
        return 1
    if len(argv) > 3:
        print("Too many args")
        return 1
    string = argv[1]
    words: List
    if len(argv) < 3:
        separator = ''
    else:
        separator = argv[2]

    try:
        words = string.split(separator)
    except:
        words = list(string)

    ans = find_combos(words)
    for i in range(0, len(ans)):
        print(separator.join(ans[i]))


main()
