import sys
from collections import deque

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]


R, C = map(int, sys.stdin.readline().split())
graph = [list(sys.stdin.readline().rstrip()) for _ in range(R)]
ans = 'IMPOSSIBLE'
q = deque()
fires = deque()
for i in range(R):
    for j in range(C):
        if graph[i][j] == 'J':
            q.append((i, j))
            graph[i][j] = '.'
        elif graph[i][j] == 'F':
            fires.append((i, j))

res = 0
GOING = True
while GOING:
    res += 1
    temp = []
    while fires:
        x, y = fires.popleft()
        for i in range(4):
            nx, ny = x + dx[i], y + dy[i]
            if 0 <= nx < R and 0 <= ny < C:
                if graph[nx][ny] == '.' or graph[nx][ny] == '$':
                    temp.append((nx, ny))
                    graph[nx][ny] = 'F'
    fires = deque(temp)

    temp = []
    while q:
        x, y = q.popleft()
        if x == 0 or y == 0 or x == R - 1 or y == C - 1:
            print(res)
            GOING = False
            exit()

        for i in range(4):
            nx, ny = dx[i] + x, dy[i] + y
            if 0 <= nx < R and 0<=ny < C and graph[nx][ny] == '.':
                temp.append((nx, ny))
                graph[x][y] = '$'
                graph[nx][ny] = 'J'
    q = deque(temp)
    if not q:
        GOING =False
else:
    print("IMPOSSIBLE")