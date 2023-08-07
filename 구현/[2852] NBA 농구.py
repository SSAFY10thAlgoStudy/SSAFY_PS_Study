import sys


def timeToString(second):
    m, s = divmod(second, 60)
    return f"{m:02d}:{s:02d}"


def stringToTime(string):
    m, s = map(int, string.split(':'))
    return m * 60 + s


N = int(sys.stdin.readline())
query = [list(map(str, sys.stdin.readline().split())) for _ in range(N)] + [['_', '48:00']]

one, two, os, ts = 0, 0, 0, 0

for i in range(N):
    teamA, timeA = query[i]
    teamB, timeB = query[i + 1]

    if teamA == '1':
        one += 1
    else:
        two += 1

    a, b = stringToTime(timeA), stringToTime(timeB)
    if one > two:
        os += (b - a)
    elif one < two:
        ts += (b - a)

print(timeToString(os))
print(timeToString(ts))
