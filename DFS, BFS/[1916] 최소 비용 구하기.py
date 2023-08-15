import heapq
import sys
from collections import defaultdict

# --------- 입력 구문 ---------
N = int(sys.stdin.readline())
M = int(sys.stdin.readline())
bus = defaultdict(list)
for _ in range(M):
    s, a, e = map(int, sys.stdin.readline().split())
    bus[s].append((a, e))
start, end = map(int, sys.stdin.readline().split())
# ---------------------------

# 출발점 기준 최단 거리를 저장하기 위해 distance 배열 선언
distance = [float('inf')] * (N + 1)
# 현재까지 값과 출발점을 tuple 형식으로 저장
heap = [(0, start)]

while heap:
    # 힙 정렬을 이용해 value 값이 가장 낮은 쌍을 pop
    value, start = heapq.heappop(heap)
    # 현재 distance 배열에 저장된 start 값이 탐색을 위해 pop 값과 비교를 하여 더 큰 경우는 탐색이 무의미하므로
    # continue 건너뛴다.
    if distance[start] < value:
        continue

    # 해당 출발지 기점으로 연결된 노드들을 탐색한다.
    for b in bus[start]:
        # a : 도착지, e : 가중치 값
        a, e = b
        # 이동하면서 쌓아온 값과 다음 가중치 값을 더한 것이 저장된 distance 배열과 비교를 했을 때
        # 더 작다면 다음 탐색이 유의미하고 반대라면 무의미.
        if value + e < distance[a]:
            distance[a] = value + e
            # 파이썬 heap 자료구조는 쌍으로 저장된 값은 앞 쪽부터 비교를 통해 힙정렬을 진행한다.
            heapq.heappush(heap, (value + e, a))

print(distance[end])
