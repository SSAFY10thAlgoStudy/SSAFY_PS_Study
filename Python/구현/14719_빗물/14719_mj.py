import sys

# 한층씩 살펴보면서 그 층에 얼마나 쌓일 수 있는지 찾고 다 더하면 될듯
# 2차원 배열에 0 1로 건물 있는곳 없는곳 처리

h, w = map(int, sys.stdin.readline().split())
height = list(map(int, sys.stdin.readline().split()))
building = [[0 for _ in range(w)] for _ in range(h)]

for i in range(w):
    for j in range(height[i]):
        building[j][i] = 1

idx = [[] for _ in range(h)]
for i in range(h):
    for j in range(w):
        if building[i][j] == 1:
            idx[i].append(j)
# i번째 층 돌면서 블록 있는 곳 인덱스 저장

result = 0
for i in range(h):
    tmp = 0
    if len(idx[i]) != 1: # 블록이 하나밖에 없으면 물 안고이니까 그거 뺌
        for j in range(len(idx[i]) - 1):
            water = idx[i][j + 1] - idx[i][j] - 1 # 중간에 고이는 물
            tmp += water
    result += tmp
print(result)
