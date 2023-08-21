import sys
sys.setrecursionlimit(10**9)
# def find(x):
#     if parents[x] != x:
#         return find(parents[x])
#     return parents[x]
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

N, M = map(int, sys.stdin.readline().split())
parents = list(range(N+1))

for m in range(M):
    cmd, a, b = map(int, sys.stdin.readline().split())
    if cmd == 0:
        union(a, b)
    else:
        if find(a) == find(b):
            print("YES")
        else:
            print("NO")
