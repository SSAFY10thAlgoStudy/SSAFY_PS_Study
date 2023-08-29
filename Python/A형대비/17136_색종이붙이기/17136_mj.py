import sys


def check(r, c, size):  # r, c에 한변이 size인 종이를 붙힐 수 있는지 확인
    for i in range(size + 1):  # size만큼 보면서
        for j in range(size + 1):
            if data[r + i][c + j] != 1:  # 1이 아니면 붙힐수 없으니까
                return False
    return True


def back(x, y, cnt):  # [x][y] 1이면 색종이 붙혀보고 붙힐 수 있으면 cnt 하나 늘려줌
    global result
    if x >= 10:  # 밑으로 넘어가면 끝
        result = min(result, cnt)
        return
    if y >= 10:  # 옆으로 넘어가면 밑에 줄 처음부터 다시 실행
        back(x + 1, 0, cnt)
        return
    if data[x][y] == 1:  # 색종이 붙힐 수 있으면
        for idx in range(5):  # 크기 1~5 붙혀보면서
            if paperCnt[idx] == 0:  # 색종이 안남아있으면
                continue  # 다음으로
            if x + idx >= 10 or y + idx >= 10:  # 색종이 붙힐곳이 범위 넘어가면
                break  # 어차피 더 큰 건 못붙히니까 끝
            if check(x, y, idx):  # idx 크기의 색종이 붙힐 수 있으면
                for i in range(idx + 1):
                    for j in range(idx + 1):
                        data[x + i][y + j] = -1  # 붙혔다고 표시
                paperCnt[idx] -= 1  # 붙힌 종이 하나 빼주고
                back(x, y + idx + 1, cnt + 1)  # 다음 칸으로 넘어감
                paperCnt[idx] += 1  # 원복
                for i in range(idx + 1):  # 원복
                    for j in range(idx + 1):
                        data[x + i][y + j] = 1
    else:  # 색종이 못붙히는 칸이면
        back(x, y + 1, cnt)  # 다음 칸에서 똑같이 실행


data = [list(map(int, sys.stdin.readline().split())) for _ in range(10)]

paperCnt = [5 for _ in range(5)]  # 색종이 몇 개 썼는지 확인
result = 10e9

back(0, 0, 0)

if result == 10e9:  # 갱신 안됐으면
    print(-1)
else:
    print(result)
