import sys

n, m = map(int, sys.stdin.readline().split())
data = list(map(int, sys.stdin.readline().split()))

for _ in range(m):
    data.sort() # 가장 작은 거 합쳐야지 최소 됨
    tmp = data[0] + data[1] # 합치고
    data[0], data[1] = tmp, tmp # 덮어씀
print(sum(data))
