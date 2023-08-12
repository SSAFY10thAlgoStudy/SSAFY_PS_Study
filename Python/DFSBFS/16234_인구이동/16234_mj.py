import sys
from collections import deque

N, L, R = map(int, sys.stdin.readline().split())
data = [list(map(int, sys.stdin.readline().split())) for _ in range(N)]


def bfs(r, c):  # 연합 한 덩어리 구해서 인구 나눠주는 함수
    queue = deque([[r, c]])  # dfs를 위한 큐
    visited[r][c] = True  # 맨 처음 방문처리
    dx = [1, -1, 0, 0]
    dy = [0, 0, 1, -1]
    coord = [[r, c]]  # 연합에 있는 나라들 좌표 저장하는 배열
    while queue:
        x, y = queue.popleft()
        for i in range(4):
            nx, ny = x + dx[i], y + dy[i]
            if 0 <= nx < N and 0 <= ny < N and not visited[nx][ny]:  # 범위 안에 있고 방문 안한 나라이고
                if L <= abs(data[x][y] - data[nx][ny]) <= R:  # 인구 차가 L이상 R이하이면
                    queue.append([nx, ny])  # 큐에 다음 좌표 넣고
                    visited[nx][ny] = True  # 방문처리 하고
                    coord.append([nx, ny])  # 연합에 추가
    if len(coord) == 1:  # 인구이동 없었을 때
        return False
    popsum = 0  # 연합에 있는 사람들 다 더할 변수
    for c in coord:
        popsum += data[c[0]][c[1]]  # 사람 전체 명수 구하고
    people = popsum // len(coord)  # 각 칸의 인구수 구해서
    for c in coord:
        data[c[0]][c[1]] = people  # 나라마다 넣어줌
    return True  # 인구이동 완료 했을 때


result = 0
while True:
    visited = [[False for _ in range(N)] for _ in range(N)]  # 매일마다 visited 배열 갱신
    canMove = False  # 더 이동 가능한지 여부 판별하는 변수
    for i in range(N):  # 모든 나라 돌면서
        for j in range(N):
            if not visited[i][j]:  # 해당 나라 방문하지 않았으면
                canMove |= bfs(i, j)  # bfs실행해서 canMove에 boolean 합 해줌
                # 하나라도 이동 해서 true return했으면 날짜 추가해야되니까
    if not canMove:  # 모든 나라에서 인구이동 없었으면
        break
    result += 1
print(result)
