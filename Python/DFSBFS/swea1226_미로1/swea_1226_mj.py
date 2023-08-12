import sys


def dfs(r, c):
    dx = [1, -1, 0, 0]
    dy = [0, 0, 1, -1]
    stack = [[r, c]]
    while stack:  # stack이 빌 때까지
        x, y = stack.pop()
        for idx in range(4):
            nx = x + dx[idx]
            ny = y + dy[idx]
            if 0 <= nx < 16 and 0 <= ny < 16:  # 범위 안에 있고
                if maze[nx][ny] == 0:  # 갈 수 있는 곳이면
                    stack.append([nx, ny])  # stack에 추가
                    maze[nx][ny] = -1  # 지나온 길이라고 표시
                elif maze[nx][ny] == 3:  # 끝점에 도착했으면
                    return 1
    return 0


for _ in range(10):
    t = int(sys.stdin.readline().strip())
    maze = [list(map(int, list(sys.stdin.readline().strip()))) for _ in range(16)]
    startx, starty = 0, 0
    for i in range(16):
        for j in range(16):
            if maze[i][j] == 2:  # 시작점 저장
                startx, starty = i, j
    print("#{} {}".format(t, dfs(startx, starty)))
