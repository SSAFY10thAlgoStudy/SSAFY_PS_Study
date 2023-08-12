import sys
from collections import deque

a, b = map(int, sys.stdin.readline().split())


def bfs(start):
    queue = deque([[start, 1]])  # 처음 위치에서 시작해서
    while queue:
        r, cnt = queue.popleft()  # cnt는 연산 횟수 저장하는 변수
        if 2 * r <= b:  # 2배한게 b보다 작으면
            queue.append([2 * r, cnt + 1])  # 큐에 넣어주고
        if int(str(r) + "1") <= b:  # 뒤에 1 붙힌게 b보다 작으면
            queue.append([int(str(r) + "1"), cnt + 1])
        if r == b:  # b를 만들었으면
            return cnt
    return -1  # 못만들었으면


print(bfs(a))
