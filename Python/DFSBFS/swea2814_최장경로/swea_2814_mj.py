import sys

T = int(sys.stdin.readline().strip())


def dfs(start, cnt):
    global result
    if cnt > result:
        result = cnt
    visited[start] = True  # 현재 위치도 방문처리해주고
    for elt in graph[start]:
        if not visited[elt]:
            visited[elt] = True
            dfs(elt, cnt + 1)
            visited[elt] = False
    visited[start] = False  # 초기화도 해줘야됨


for t in range(1, T + 1):
    n, m = map(int, sys.stdin.readline().split())
    graph = [[] for _ in range(n + 1)]
    visited = [False for _ in range(n + 1)]
    for _ in range(m):
        a, b = map(int, sys.stdin.readline().split())
        graph[a].append(b)
        graph[b].append(a)
    result = 0
    for i in range(1, n + 1):
        dfs(i, 1)
    print("#{} {}".format(t, result))
