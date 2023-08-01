import sys
from collections import deque


def dist(x1, y1, x2, y2):
    # 맨해튼 거리로 구하는 두 점 사이의 거리
    return abs(x1 - x2) + abs(y1 - y2)


def dfs(start):
    queue = deque([start])
    visited[start] = True
    while queue:
        r = queue.popleft()
        if dist(data[r][0], data[r][1], data[-1][0], data[-1][1]) <= 20 * 50: # 편의점 위치에서 송도에 도착 가능하면
            return "happy"
        for i in range(1, n + 2):  # 편의점들만 탐색
            d = dist(data[r][0], data[r][1], data[i][0], data[i][1])
            if not (visited[i]) and d <= 20 * 50: # 방문하지 않은 편의점이고 맥주 20개 안에 갈 수 있으면
                visited[i] = True
                queue.append(i)
    return "sad"


t = int(sys.stdin.readline().strip())
for _ in range(t):
    n = int(sys.stdin.readline().strip())
    data = [list(map(int, sys.stdin.readline().split())) for _ in range(n + 2)]
    visited = [False for _ in range(n + 2)]
    print(dfs(0))
