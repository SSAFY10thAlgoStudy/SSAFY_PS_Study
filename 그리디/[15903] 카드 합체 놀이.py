import heapq
import sys

n, m = map(int, sys.stdin.readline().split())
nums = list(map(int, sys.stdin.readline().split()))
heapq.heapify(nums)
for _ in range(m):
    temp = heapq.heappop(nums) + heapq.heappop(nums)
    heapq.heappush(nums, temp)
    heapq.heappush(nums, temp)

print(sum(nums))


