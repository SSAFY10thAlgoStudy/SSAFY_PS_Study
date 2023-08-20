import sys
from collections import deque

A, B = map(int, sys.stdin.readline().split())
q = deque()
q.append((A, 1))
# chk = [False] * (B + 1)
while q:
    value, count = q.popleft()
    if value > B:
        continue
    if value == B:
        print(count)
        break
    # if value <= B and not chk[value]:
        # chk[value] = True

    q.append((value * 2, count + 1))
    q.append((int(str(value) + "1"), count + 1))
else:
    print(-1)