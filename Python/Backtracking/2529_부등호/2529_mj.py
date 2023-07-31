import sys

k = int(sys.stdin.readline().strip())
inequality = sys.stdin.readline().strip().split()
visited = [0 for _ in range(10)]
result = []


def dfs(cnt, formula):
    if cnt == k + 1:
        result.append(formula)
        return
    for i in range(10):
        if visited[i] == 0:
            if cnt == 0 or eval(formula[-1] + inequality[cnt - 1] + str(i)):
                visited[i] = 1
                dfs(cnt + 1, formula + str(i))
                visited[i] = 0


dfs(0, "")
print(result[-1])
print(result[0])
