import sys
import datetime as dt

n = int(sys.stdin.readline().strip())
data = []
for _ in range(n):
    a, b = sys.stdin.readline().split()
    data.append([int(a), list(map(int, b.split(":")))])

win1, win2 = dt.datetime(2023, 1, 1, 0, 0, 0), dt.datetime(2023, 1, 1, 0, 0, 0)
winner = {1: 0, 2: 0}
for i in range(n - 1):
    winner[data[i][0]] += 1
    if winner[1] > winner[2]:  # 1이 이기고 있을 때
        # 년 월 일 시간 분 초
        dt1 = dt.datetime(2023, 1, 1, 1, data[i][1][0], data[i][1][1])
        dt2 = dt.datetime(2023, 1, 1, 1, data[i + 1][1][0], data[i + 1][1][1])
        td = dt2 - dt1
        win1 += td
    elif winner[1] < winner[2]:
        dt1 = dt.datetime(2023, 1, 1, 1, data[i][1][0], data[i][1][1])
        dt2 = dt.datetime(2023, 1, 1, 1, data[i + 1][1][0], data[i + 1][1][1])
        td = dt2 - dt1
        win2 += td

winner[data[-1][0]] += 1
if winner[1] > winner[2]:
    dt1 = dt.datetime(2023, 1, 1, 1, data[-1][1][0], data[-1][1][1])
    end = dt.datetime(2023, 1, 1, 1, 48, 0)
    td = end - dt1
    win1 += td
elif winner[1] < winner[2]:
    dt2 = dt.datetime(2023, 1, 1, 1, data[-1][1][0], data[-1][1][1])
    end = dt.datetime(2023, 1, 1, 1, 48, 0)
    td = end - dt2
    win2 += td

temp1 = win1 - dt.datetime(2023, 1, 1, 0, 0, 0)
temp2 = win2 - dt.datetime(2023, 1, 1, 0, 0, 0)
print(str(temp1)[2:])
print(str(temp2)[2:])
