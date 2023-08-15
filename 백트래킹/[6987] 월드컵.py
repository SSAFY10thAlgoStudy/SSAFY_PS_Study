import itertools
import sys


def bt(index):
    global answer
    # 종료 조건
    if index == 15:
        if not sum([sum(r) for r in result]):
            answer = 1
        return
    x, y = match[index]
    for i in range(3):
        if result[x][dx[i]] > 0 and result[y][dy[i]] > 0:
            result[x][dx[i]] -= 1
            result[y][dy[i]] -= 1
            bt(index + 1)
            result[x][dx[i]] += 1
            result[y][dy[i]] += 1


dx = [2, 1, 0]
dy = [0, 1, 2]
match = list(itertools.combinations([0, 1, 2, 3, 4, 5], 2))
for _ in range(4):
    # [5, 0, 0, 3, 0, 2, 2, 0, 3, 0, 0, 5, 4, 0, 1, 1, 0, 4]
    score = list(map(int, sys.stdin.readline().split()))
    # [[5, 0, 0], [3, 0, 2], [2, 0, 3], [0, 0, 5], [4, 0, 1], [1, 0, 4]]
    result = [score[i:i + 3] for i in range(0, 18, 3)]
    answer = 0
    bt(0)
    print(answer, end=" ")
