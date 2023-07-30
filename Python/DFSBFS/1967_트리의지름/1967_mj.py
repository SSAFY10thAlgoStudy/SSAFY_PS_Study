# https://www.acmicpc.net/problem/1967
import sys
from collections import deque

n = int(sys.stdin.readline().strip())
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    a, b, c = map(int, sys.stdin.readline().split())
    graph[a].append([b, c])
    graph[b].append([a, c])


def bfs(r):
    visited = [-1 for _ in range(n + 1)]
    queue = deque([r])
    visited[r] = 0
    radius, center = -1, -1
    while queue:
        u = queue.popleft()
        for i, d in graph[u]:
            if visited[i] == -1:
                visited[i] = visited[u] + d
                queue.append(i)
                if visited[i] > radius:
                    radius, center = visited[i], i
    return [radius, center]


if n == 1: # 점이 하나일때 예외처리
    print(0)
else:
    _, node = bfs(1)
    r, _ = bfs(node)
    print(r)
