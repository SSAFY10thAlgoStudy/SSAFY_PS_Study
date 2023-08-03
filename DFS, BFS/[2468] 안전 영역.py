import sys
sys.setrecursionlimit(10**6)
ri = [0, 0, 1, -1]
rj = [1, -1, 0, 0]
def dfs(i, j):
    global N
    for _ in range(4):
        ni = ri[_] + i
        nj = rj[_] + j
        if 0 <= ni < N and 0 <= nj < N:
            if not chk[ni][nj] and not sink[ni][nj]:
                chk[ni][nj] = True
                dfs(ni, nj)
N = int(sys.stdin.readline())
graph = [list(map(int, sys.stdin.readline().split())) for _ in range(N)]

max_height = max([max(g) for g in graph])
sink = [[False] * N for _ in range(N)]
max_count = 1
for h in range(1, max_height):
    for i in range(N):
        for j in range(N):
            if graph[i][j] <= h:
                sink[i][j] = True
    count = 0
    chk = [[False] * N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            if not sink[i][j] and not chk[i][j]:
                count += 1
                chk[i][j] = True
                dfs(i, j)

    max_count = max(max_count, count)
print(max_count)
