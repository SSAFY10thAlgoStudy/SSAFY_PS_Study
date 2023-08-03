import sys
sys.setrecursionlimit(10**9)
def dfs(s, k):
    global answer, start
    check[s] = True
    for i, j in graph[s]:
        if not check[i]:
            if answer <= k + j:
                answer = k + j
                start = i
            dfs(i, k+j)

N = int(sys.stdin.readline())
graph = [[] for _ in range(N+1)]
for _ in range(N-1):
    a, b, e = map(int, sys.stdin.readline().split())
    graph[a].append([b, e])
    graph[b].append([a, e])

check = [False] * (N+1)
answer = 0
diff = []
start = -1
answer = float("-inf")
dfs(1, 0)
check = [False] * (N+1)
answer = float('-inf')
dfs(start, 0)
print(answer) if answer != float('-inf')else print(0)