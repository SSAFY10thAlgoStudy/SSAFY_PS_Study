import sys
from collections import deque

n, k = map(int, sys.stdin.readline().split())
an = deque(map(int, sys.stdin.readline().split()))
robot = deque([0] * n)

result = 0
while True:
    result += 1
    an.rotate(1)  # 벨트 회전
    robot[-1] = 0  # 맨 마지막 무조건 내림
    robot.rotate(1)  # 로봇 회전
    robot[-1] = 0
    for i in range(n - 2, -1, -1):  # 가장 먼저 올라간 거부터 i.e 뒤에서부터
        if robot[i + 1] == 0 and an[i + 1] >= 1 and robot[i] == 1:
            # 다음칸 로봇 없고 내구도 1이상 이고 내 위에 로봇 있으면
            robot[i + 1] = 1  # 한칸 이동
            robot[i] = 0  # 내꺼 없앰
            an[i + 1] -= 1  # 내구도 내려감
    robot[-1] = 0  # 맨 마지막 무조건 내림
    if robot[0] != 1 and an[0] != 0:  # 맨 처음에 로봇 없고 내구도 0 아니면
        robot[0] = 1  # 로봇 놓고
        an[0] -= 1  # 내구도 내림

    if an.count(0) >= k:  # 0이 k개 이상일때
        break

print(result)
