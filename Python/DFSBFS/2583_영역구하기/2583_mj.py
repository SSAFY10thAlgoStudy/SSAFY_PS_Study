import sys
from collections import deque

m, n, k = map(int, sys.stdin.readline().split())

board = [[0 for _ in range(n)] for _ in range(m)]
visited = [[False for _ in range(n)] for _ in range(m)]

for _ in range(k):
    x1, y1, x2, y2 = map(int, sys.stdin.readline().split())
    for i in range(x1, x2):
        for j in range(y1, y2):
            board[j][i] = 1


# 보드가 0인곳부터 탐색해서 그거랑 연결되어 있는 곳 중 0인곳이 몇개인지 세고 visited 갱신 시키면서 탐색
# 그렇게 해서 연결된 부분 다 찾으면 넓이 return 해서 리스트에 넣고 다음 0이고 안간곳 탐색

def bfs(r, c):
    cnt = 1  # 지금 현재 위치 넓이로 초기화
    queue = deque([[r, c]])
    visited[r][c] = True
    dx = [0, 0, 1, -1]
    dy = [1, -1, 0, 0]
    while queue:
        x, y = queue.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if 0 <= nx < m and 0 <= ny < n:  # 보드 안에 있고
                if board[nx][ny] == 0 and not (visited[nx][ny]):  # 사각형 아니고 방문한적 없으면
                    queue.append([nx, ny])
                    visited[nx][ny] = True
                    cnt += 1  # 넓이 하나 늘려줌
    return cnt  # 다 탐색하고 넓이 return


result = []

for i in range(m):
    for j in range(n):
        if board[i][j] == 0 and not (visited[i][j]):
            result.append(bfs(i, j))  # 사각형 없고 방문하지 않은 곳에서만 bfs실행

print(len(result))  # 영역의 개수
print(*sorted(result))  # 넓이 오름차순 정렬 후 출력
