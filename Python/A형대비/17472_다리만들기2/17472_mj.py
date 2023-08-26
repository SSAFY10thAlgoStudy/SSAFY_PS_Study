import sys
from collections import deque

dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]


def connect(r, c):  # 섬의 한 점에서 상하좌우 탐색해서 다른 섬이랑 이어지는 다리 다 찾기
    bridgeList = []
    for idx in range(4):
        nx = r + dx[idx]  # 일단 한 칸 옮겨보고
        ny = c + dy[idx]
        if nx < 0 or nx >= n or ny < 0 or ny >= m:  # 범위 벗어났으면 다음으로
            continue
        if board[nx][ny] == 1:  # 한칸 옮겼는데 1이면 다리 안됨
            continue
        cnt = 0
        while 0 <= nx < n and 0 <= ny < m:  # 범위 안에 있을 동안
            if board[nx][ny] == 0:  # 현재 칸에 다리 놓을 수 있었으면
                cnt += 1  # 다리 길이 증가
                nx += dx[idx]  # 같은 방향으로 전진
                ny += dy[idx]
            else:
                if cnt != 1:  # 다리 길이 1이면 안됨
                    bridgeList.append([[r, c], [nx, ny], cnt])  # 시작점, 도착점, 다리길이
                break
    return bridgeList


def bfs(r, c):  # 섬 하나 좌표들 찾는 함수
    queue = deque([[r, c]])
    visited[r][c] = True
    island = [[r, c]]  # 이어진 땅 좌표 담을 배열
    while queue:
        x, y = queue.popleft()
        for idx in range(4):
            nx = x + dx[idx]
            ny = y + dy[idx]
            if 0 <= nx < n and 0 <= ny < m:  # 범위 안에 있고
                if not visited[nx][ny] and board[nx][ny] == 1:  # 연결 되어 있고 땅이면
                    visited[nx][ny] = True  # 방문처리
                    queue.append([nx, ny])
                    island.append([nx, ny])  # 섬 목록에 넣기
    return island


def findRoot(tree, x):  # x의 루트 노드 찾는 함수
    if tree[x] != x:
        return findRoot(tree, tree[x])
    return tree[x]


def unionSet(tree, x, y):  # x, y를 합집합 하는 함수
    x = findRoot(tree, x)
    y = findRoot(tree, y)
    if x <= y:
        tree[y] = x
    else:
        tree[x] = y


n, m = map(int, sys.stdin.readline().split())

board = [list(map(int, sys.stdin.readline().split())) for _ in range(n)]

bridge = []  # 다리 정보 저장할 배열

islandDict = {}  # 하나의 섬 좌표 저장할 딕셔너리

islandNum = 1  # 섬 번호 1부터 시작
visited = [[False for _ in range(m)] for _ in range(n)]  # 방문처리 배열

for i in range(n):  # 다 돌면서
    for j in range(m):
        if board[i][j] == 1:  # 땅이면
            bridge.extend(connect(i, j))  # 연결 할 수 있는 다리 다 연결하고
            if not visited[i][j]:  # 가지 않은 점이면
                islandDict[islandNum] = bfs(i, j)  # 그 점이 속한 섬 좌표로 받아서 넣고
                islandNum += 1  # 다음 섬 탐색

result = 0  # 최종 다리 길이 저장하기 위해서

bridge.sort(key=lambda x: x[-1])  # 크루스칼 쓰기 위해 비용으로 정렬
parents = [i for i in range(islandNum)]  # 섬들 union find 하기 위함
islandVisited = [False for _ in range(islandNum)]  # 섬 방문처리
startIsland, endIsland = -1, -1  # 좌표가 있는 섬의 번호 저장

for i in range(len(bridge)):  # 다리 리스트 다 돌면서
    start, end, length = bridge[i]
    for key, value in islandDict.items():
        if start in value:  # 시작점이 있는 섬 번호 받고
            startIsland = key
        if end in value:  # 끝점이 있는 섬 번호 받고
            endIsland = key
    if findRoot(parents, startIsland) != findRoot(parents, endIsland):  # 만약 아직 연결 안됐으면
        unionSet(parents, startIsland, endIsland)  # 연결 해주고
        result += length  # 다리 길이 추가

check = set()  # 전부 연결되어있는지 확인 위해서
for i in range(1, islandNum):
    check.add(findRoot(parents, i))  # 섬의 루트노드 다 찾아서

if len(check) == 1:  # 루트노드가 다 같았으면
    print(result)  # 결과 출력
else:  # 연결 안된곳 있으면
    print(-1)
