import sys

data = [list(map(int, list(sys.stdin.readline().strip()))) for _ in range(9)]

for i in range(9):
    for j in range(9):
        if data[i][j] == 0:
            row = [data[i][k] for k in range(9) if data[i][k] != 0]
            column = [data[k][j] for k in range(9) if data[k][j] != 0]

            # 사각형영역 처리 해줘야함

            tmp = list(set(row).union(set(column)))
            tmp.sort()
            for l in range(1, 10):
                if l not in tmp:
                    data[i][j] = l
                    break

for i in range(9):
    print(*data[i])
