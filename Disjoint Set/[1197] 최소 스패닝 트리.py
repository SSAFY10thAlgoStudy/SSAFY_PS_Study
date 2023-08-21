import sys
from collections import defaultdict
import heapq


def find(x):
    if parents[x] != x:
        parents[x] = find(parents[x])
    return parents[x]


def union(x, y):
    x = find(x)
    y = find(y)

    # 더 작은 루트노드에 합친다.
    if x < y:
        parents[y] = x
    else:
        parents[x] = y


V, E = map(int, sys.stdin.readline().split())
graph = defaultdict(list)
heap = []
for _ in range(E):
    a, b, c = map(int, sys.stdin.readline().split())
    heapq.heappush(heap, (c, a, b))
parents = [i for i in range(V + 1)]

edges = 0
values = 0
while heap:
    value, a, b = heapq.heappop(heap)
    if edges == V - 1:
        break
    if find(a) != find(b):
        union(a, b)
        values += value
        edges += 1
print(values)