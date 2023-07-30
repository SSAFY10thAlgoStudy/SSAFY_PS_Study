import sys
from collections import deque

r, c = map(int, sys.stdin.readline().split())

maze = [list(sys.stdin.readline().strip()) for _ in range(r)]
fireLoc = []  # 불 여러 곳에서 시작 가능

for i in range(r):
    for j in range(c):
        if maze[i][j] == "J":
            now_i, now_j = i, j
        elif maze[i][j] == "F":
            fireLoc.append([i, j])

visited = [[0] * c for _ in range(r)]
fired = [[0] * c for _ in range(r)]


def bfs(my_i, my_j, fireList):
    fire_queue = deque()
    for a, b in fireList:
        fired[a][b] = 1
        fire_queue.append([a, b])
    dx = [0, 0, 1, -1]
    dy = [1, -1, 0, 0]
    while fire_queue:
        fire_x, fire_y = fire_queue.popleft()
        for idx in range(4):
            nx = fire_x + dx[idx]
            ny = fire_y + dy[idx]
            if 0 <= nx < r and 0 <= ny < c:
                if fired[nx][ny] == 0 and maze[nx][ny] != "#":
                    fired[nx][ny] = fired[fire_x][fire_y] + 1
                    fire_queue.append([nx, ny])

    visited[my_i][my_j] = 1
    my_queue = deque([[my_i, my_j]])
    while my_queue:
        my_x, my_y = my_queue.popleft()
        for idx in range(4):
            nx = my_x + dx[idx]
            ny = my_y + dy[idx]
            if 0 <= nx < r and 0 <= ny < c:
                if maze[nx][ny] != "#" and visited[nx][ny] == 0:  # 내가 갈 수 있는 곳이며 가지 않은 곳이면
                    if fired[nx][ny] == 0 or fired[nx][ny] > visited[my_x][my_y] + 1:  # 불이 아직 퍼지지 않은 곳이면
                        visited[nx][ny] = visited[my_x][my_y] + 1
                        my_queue.append([nx, ny])
            else:  # 범위를 벗어남 i.e 탈출함
                return visited[my_x][my_y]
    return "IMPOSSIBLE"


print(bfs(now_i, now_j, fireLoc))
