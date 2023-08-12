import sys
from collections import deque


def bfs(r):
    queue = deque([r])
    visited[r] = True
    while queue:
        u = queue.popleft()
        for elt in graph[u]:
            if not visited[elt]:
                visited[elt] = True
                queue.append(elt)


T = int(sys.stdin.readline().strip())
for t in range(T):
    n, m = map(int, sys.stdin.readline().split())
    graph = [[] for _ in range(n + 1)]
    visited = [False for _ in range(n + 1)]
    for _ in range(m):
        a, b = map(int, sys.stdin.readline().split())
        graph[a].append(b)
        graph[b].append(a)
    cnt = 0
    for i in range(1, n + 1):
        if not visited[i]:
            bfs(i)
            cnt += 1
    print("#{} {}".format(t + 1, cnt))
