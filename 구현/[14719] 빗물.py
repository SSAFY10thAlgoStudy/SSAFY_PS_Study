import sys

H, W = map(int, sys.stdin.readline().split())
heights = list(map(int, sys.stdin.readline().split()))
answer = 0
for w in range(1, W-1):
    lh, rh = max(heights[:w]), max(heights[w+1:])
    if min(lh, rh) > heights[w]:
        answer += min(lh, rh) - heights[w]
print(answer)