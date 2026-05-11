"""
A port of algorithm.cpp.

global variables are used to maintain consistency with the original implementation.
"""

from dataclasses import dataclass
from typing import Mapping
from collections import defaultdict
import sys


@dataclass
class Coordinate:
    x: int
    y: int

    @classmethod
    def from_line(cls, line: str):
        line = line.replace("\n", "")
        tokens = [int(t) for t in line.split(" ")]
        return cls(x=tokens[0], y=tokens[1])


def make_list_of(n: int) -> list[int]:
    """Make list of n elements."""
    l = []
    for _ in range(n):
        l.append(int())
    return l


ans: int = 0
order: list[int] = []

n = 0
coordinates: list[Coordinate] = []
yandnum = defaultdict(int)


def check():
    global n, order, coordinates, yandnum

    visited: list[int] = make_list_of(n)
    cur: Coordinate = None
    curi: int = 0

    for i in range(n):
        escape: bool = False
        cur = coordinates[i]
        curi = i

        while not escape:
            visited[curi] += 1
            realindex: int = i

            for j in range(n):
                if curi == order[j]:
                    realindex = j

            if realindex % 2 == 0:
                cur = coordinates[order[realindex + 1]]
                curi = order[realindex + 1]
            else:
                cur = coordinates[order[realindex - 1]]
                curi = order[realindex - 1]

            visited[curi] += 1

            if yandnum[cur.y] >= 2:
                minx: int = 1000000001
                index: int = -1
                for j in range(n):
                    if coordinates[j].y == cur.y:
                        if coordinates[j].x > cur.x and coordinates[j].x < minx:
                            minx = coordinates[j].x
                            index = j

                if index == -1:
                    escape = True
                    break
                else:
                    cur = coordinates[index]
                    curi = index

                if visited[curi] >= 2:
                    return True

            else:
                escape = True

        for j in range(n):
            visited[j] = 0

    return False


def recursion(count: int, num1: int, num2: int, used: list[bool]):
    global order, ans

    order[count] = num1
    order[count + 1] = num2

    if count + 2 == n:
        if check():
            ans += 1
        return

    used[num1] = True
    used[num2] = True

    for i in range(num1 + 1, n):
        for j in range(i + 1, n):
            if used[i] is False and used[j] is False:
                if i > num1:
                    recursion(count + 2, i, j, used)

    used[num1] = False
    used[num2] = False


def main():
    global n, order, coordinates, yandnum

    print("Waiting for input ...")
    n = int(sys.stdin.readline())
    for line in range(n):
        line = sys.stdin.readline()
        cord = Coordinate.from_line(line)
        coordinates.append(cord)

        yandnum[cord.y] += 1

    used: list[bool] = []
    for _ in range(n):
        used.append(bool())

    for _ in range(n):
        order.append(int())

    for i in range(1, n):
        recursion(0, 0, i, used)

    print(ans)


if __name__ == "__main__":
    main()
