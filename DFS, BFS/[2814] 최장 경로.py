from collections import defaultdict
def dfs(start, value):
    global end, answer
    if answer < value:
        end = start
        answer = value
    for g in graph[start]:
        if not chk[g]:
            chk[g] = True
            dfs(g, value + 1)


T = int(input())
for testcase in range(1, T+1):
    n, m = map(int, input().split())
    graph = defaultdict(list)
    for _ in range(m):
        a, b = map(int, input().split())
        graph[a].append(b)
        graph[b].append(a)
    chk = [False] * (n+1)
    answer = float('-inf')
    end = 1
    chk[1] = True
    dfs(1, 1)
    print(end, answer)
    chk = [False] * (n+1)
    chk[end] = True
    dfs(end, 1)
    print("#{} {}".format(testcase, answer))
    # print(answer, end)
    