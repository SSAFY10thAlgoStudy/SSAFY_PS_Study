import sys
AREA = {3 : (0, 0), 4 : (0, 3), 5 : (0, 6), 6 : (3, 0), 7 : (3, 3), 8 : (3, 6), 9 : (6, 0), 10 : (6, 3), 11 : (6, 6)}
def areaCheck(x, y):
    area = 0
    #스도쿠 9군데 중 어딘지 확인
    if 0 <= x < 3:
        area += 3
    elif 3 <= x < 6:
        area += 6
    else:
        area += 9

    if 0 <= y < 3:
        area += 0
    elif 3 <= y < 6:
        area += 1
    else:
        area += 2
    return AREA[area]
def check(ix, iy, v):
    # 한줄 체크 과정
    for i in range(9):
        if i != ix and graph[i][iy] == v or graph[ix][i] == v:
            return False
    # 3x3 박스 체크 과정
    sx, sy = areaCheck(ix, iy)
    for i in range(sx, sx + 3):
        for j in range(sy, sy + 3):
            if graph[i][j] == v:
                return False
    return True
def sudoku(t):
    if t == len(zero):
        for z in range(9):
            print(''.join(map(str, graph[z])))
        exit()

    i, j = zero[t]
    for number in range(1, 10):
        if check(i, j, number):
            graph[i][j] = number
            sudoku(t + 1)
            graph[i][j] = 0
graph = [list(map(int, sys.stdin.readline().rstrip())) for _ in range(9)]
zero = []
for x in range(9):
    for y in range(9):
        if not graph[x][y]:
            zero.append((x, y))
sudoku(0)