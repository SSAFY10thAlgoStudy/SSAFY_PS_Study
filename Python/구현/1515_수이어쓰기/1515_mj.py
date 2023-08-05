import sys
from collections import deque

data = deque(list(sys.stdin.readline().strip()))

n = 0
while data:
    n += 1
    tmp = str(n)
    for t in tmp:
        if t == data[0]:
            data.popleft()
        if len(data) == 0:  # pop하다가 data 없어지면 for문 종료
            break
print(n)

# 주어진 숫자 큐에 넣고 n을 하나씩 늘려가면서
# 맨 앞에 있는 문자가 n에 있는 문자와 같으면 pop
