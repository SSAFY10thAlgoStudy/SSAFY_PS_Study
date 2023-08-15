import heapq
from copy import deepcopy

dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]
T = int(input())
for testcase in range(1, T + 1):
    N, M, K = map(int, input().split())
    graph = [list(map(int, input().split())) for _ in range(N)]
    chk = set()
    heap = []
    for x in range(N):
        for y in range(M):
            if graph[x][y] != 0:
                chk.add((x, y))
                heapq.heappush(heap, (graph[x][y], x, y, graph[x][y]))

    for k in range(K):
        tmp = []
        while heap:
            t, x, y, origin = heapq.heappop(heap)
            if t + origin == 0:
                continue
            if t == 0:
                for i in range(4):
                    nx = x + dx[i]
                    ny = y + dy[i]
                    if (nx, ny) not in chk:
                        chk.add((nx, ny))
                        heapq.heappush(tmp, (origin, nx, ny, origin))
            if t - 1 + origin != 0:
                heapq.heappush(tmp, (t - 1, x, y, origin))
        heap = deepcopy(tmp)
    print("#{} {}".format(testcase, len(heap)))
