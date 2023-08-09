import sys

r, c, t = map(int, sys.stdin.readline().split())
given = [list(map(int, sys.stdin.readline().split())) for _ in range(r)]

cleaner = []
for x in range(r):  # 공청기의 위치 저장
    for y in range(c):
        if given[x][y] == -1:
            cleaner.append([x, y])


def spread(data):  # 확산시키는 함수
    result = [[0] * c for _ in range(r)]
    dx = [0, 0, 1, -1]
    dy = [1, -1, 0, 0]
    for x in range(r):
        for y in range(c):
            if data[x][y] == -1:  # 공청기 위치에 넣어줌
                result[x][y] = -1
            if data[x][y] > 0:
                result[x][y] += data[x][y]  # 기준점 농도 저장
                for idx in range(4):
                    nx = x + dx[idx]
                    ny = y + dy[idx]
                    if 0 <= nx < r and 0 <= ny < c and data[nx][ny] != -1:  # 범위 안에 있고 공청기가 아니면
                        result[nx][ny] += data[x][y] // 5  # 확산시키고
                        result[x][y] -= (data[x][y] // 5)  # 내꺼에서는 빼줌
    return result


def clean(data):
    result = [[0] * c for _ in range(r)]
    # 위쪽 공청기
    cl_x, cl_y = cleaner[0][0], c
    data[cleaner[0][0]][cleaner[0][1]] = 0  # 공청기 위치에서 시작하는건 0이니까 임시로 넣어줌(나중에 -1로 치환)
    for i in range(1, cl_x):
        result[i][0] = data[i - 1][0]
    for i in range(cl_y - 1):
        result[0][i] = data[0][i + 1]
    for i in range(cl_x):
        result[i][-1] = data[i + 1][-1]
    for i in range(cl_y - 1):
        result[cl_x][i + 1] = data[cl_x][i]

    # 밑쪽 공청기
    cl_x, cl_y = cleaner[1][0], c
    data[cleaner[1][0]][cleaner[1][1]] = 0  # 공청기 위치에서 시작하는건 0이니까 임시로 넣어줌(나중에 -1로 치환)
    for i in range(cl_x + 1, r - 1):
        result[i][0] = data[i+1][0]
    for i in range(cl_y):
        result[-1][i - 1] = data[-1][i]
    for i in range(cl_x - 1, r - 1):
        result[i + 1][-1] = data[i][-1]
    for i in range(cl_y - 1):
        result[cl_x][i + 1] = data[cl_x][i]

    result[cleaner[0][0]][cleaner[0][1]] = -1  # 다시 공청기 넣기
    result[cleaner[1][0]][cleaner[1][1]] = -1

    for i in range(1, r - 1):  # 공청 안되는 자리에 있던 원소 원복
        if i not in [cleaner[0][0], cleaner[1][0]]:
            for j in range(1, c - 1):
                result[i][j] = data[i][j]

    return result


answer = clean(spread(given))  # 1초 후

for _ in range(t-1): # 2초부터 t초까지 같은 작업 반복
    answer = clean(spread(answer))

ans = 0
for d in answer:
    ans += sum(d)
print(ans + 2)  # 공청기 -1 2개니까 더해줌
