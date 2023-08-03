import sys

sys.setrecursionlimit(10 ** 9)


def dfs(x, y):
    global N, M, tmp
    for _ in range(4):
        nx = x + dx[_]
        ny = y + dy[_]
        if 0 <= nx < N and 0 <= ny < M and not graph[ny][nx]:
            graph[ny][nx] = True
            tmp += 1
            dfs(nx, ny)


# 입력 케이스
M, N, K = map(int, sys.stdin.readline().split())
dots = [list(map(int, sys.stdin.readline().split())) for _ in range(K)]
graph = [[False] * N for _ in range(M)]
dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]

# 해당 좌표들 방문 처리
for dot in dots:
    sx, sy, ex, ey = dot
    for y in range(sy, ey):
        for x in range(sx, ex):
            graph[y][x] = True

answer = 0
# 영역 크기 구하기 위해 [] 선언
count = []
# x, y 탐색 진행
for y in range(M):
    for x in range(N):
        tmp = 1
        # 방문 처리 안됐다면 진행
        if not graph[y][x]:
            graph[y][x] = True
            answer += 1
            dfs(x, y)
            count.append(tmp)

print(answer)
print(*sorted(count))
