import sys

data = list(sys.stdin.readline().strip())

result = 0
stack = []
tmp = 1
for idx in range(len(data)):
    if data[idx] == "(":
        tmp *= 2  # 열리는 괄호 만나면 일단 2 곱함
        stack.append(data[idx])
    elif data[idx] == "[":
        tmp *= 3
        stack.append(data[idx])
    elif data[idx] == ")":
        if len(stack) != 0 and stack[-1] == "(":  # 만약 소괄호 짝 맞으면
            if data[idx - 1] == "(":  # 주어진 문자열에서 내 앞이 열리는 소괄호면
                result += tmp  # 지금까지 결과 더해줌
            stack.pop()
            tmp //= 2  # 닫히는 괄호 만났으니까 처음에 2 곱한거 나눠줌
        else:
            stack.append(data[idx])
    elif data[idx] == "]":
        if len(stack) != 0 and stack[-1] == "[":
            if data[idx - 1] == "[":
                result += tmp
            stack.pop()
            tmp //= 3
        else:
            stack.append(data[idx])

print(result if not stack else 0)  # stack 안비어있으면 괄호 짝 안맞은거니까 0 출력
