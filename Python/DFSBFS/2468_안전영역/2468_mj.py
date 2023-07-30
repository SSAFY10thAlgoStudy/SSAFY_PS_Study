import sys
from collections import deque

n = int(sys.stdin.readline().strip())
graph = [list(map(int, sys.stdin.readline().split())) for _ in range(n)]

MaxHeight = -1
for i in range(n):
    for j in range(n):
        if graph[i][j] > MaxHeight:
            MaxHeight = graph[i][j]


def bfs(r, c, height):
    queue = deque([[r, c]])
    visited[r][c] = 1
    dx = [0, 0, 1, -1]
    dy = [1, -1, 0, 0]
    while queue:
        x, y = queue.popleft()
        for idx in range(4):
            nx = x + dx[idx]
            ny = y + dy[idx]
            if 0 <= nx < n and 0 <= ny < n:  # 그래프 범위 안에 있고
                if graph[nx][ny] > height and visited[nx][ny] == 0:  # height층보다 높아서 잠기지 않고 방문한 적 없으면
                    visited[nx][ny] = 1
                    queue.append([nx, ny])  # 큐에 추가


result = 0
for h in range(MaxHeight):  # 0층부터 최대층-1까지 돌면서
    visited = [[0] * n for _ in range(n)]
    tmp = 0
    for i in range(n):
        for j in range(n):
            if graph[i][j] > h and visited[i][j] == 0:  # 그래프를 돌면서 해당 칸이 침수층보다 높고 방문하지 않았으면
                bfs(i, j, h)  # 해당 위치에서 bfs 실행
                tmp += 1  # 안전영역 추가
    if tmp > result:
        result = tmp

print(result)
