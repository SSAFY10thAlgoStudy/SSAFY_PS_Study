import sys


def calculate(x1, operator, x2):  # 숫자랑 연산자 받아서 계산해주는 함수
    x1 = int(x1)
    x2 = int(x2)
    if operator == '+':
        return x1 + x2
    elif operator == '*':
        return x1 * x2
    elif operator == '-':
        return x1 - x2


def back(cnt, formula):
    global result
    if cnt == n - 1:  # 전체 길이만큼 다 했으면
        result = max(result, formula)  # 정답 갱신
    if cnt + 2 < n:  # 현재 위치 괄호로 안묶고 계산
        back(cnt + 2, calculate(formula, data[cnt + 1], int(data[cnt + 2])))
    if cnt + 4 < n:  # 내 뒤에 괄호로 묶고 계산
        back(cnt + 4,
             calculate(formula, data[cnt + 1], calculate(int(data[cnt + 2]), data[cnt + 3], int(data[cnt + 4]))))


n = int(sys.stdin.readline().strip())
data = sys.stdin.readline().strip()

result = -10e9

back(0, int(data[0]))
print(result)
