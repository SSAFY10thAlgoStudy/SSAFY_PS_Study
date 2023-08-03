import sys

# test case 입력
from collections import deque, defaultdict

T = int(sys.stdin.readline())
for t in range(T):
    n = int(sys.stdin.readline())
    home = list(map(int, sys.stdin.readline().split()))
    cus = [tuple(map(int, sys.stdin.readline().split())) for _ in range(n)]
    final = list(map(int, sys.stdin.readline().split()))
    chk = defaultdict(bool)
    q = deque()
    q.append(home)
    while q:
        x, y = q.popleft()
        # 현재 지점에서 도착 지점까지 1000 차이면 현재 들고있는 맥주 20개로 가능
        if abs(final[0] - x) + abs(final[1] - y) <= 1000:
            # 도착 시 HAPPY 출력
            print("happy")
            break
        # 최단 거리 BFS 이용해서 도달 가능한 주변 편의점 탐색
        for cu in cus:
            nx, ny = cu
            # 위와 같은 조건
            if abs(nx - x) + abs(ny - y) <= 1000 and not chk[cu]:
                chk[cu] = True
                q.append(cu)
    else:
        # 도착 못하고 도달 지점 없으면 SAD 출력
        print("sad")



