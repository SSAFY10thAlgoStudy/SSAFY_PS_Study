import sys

word = sys.stdin.readline().rstrip()
stack = []
temp = 1
answer = 0

for i in range(len(word)):
    w = word[i]
    if w in '([':
        temp *= 2 if w == '(' else 3
        stack.append(w)
    else:
        if not stack or (w == ')' and stack[-1] != '(') or (w == ']' and stack[-1] != '['):
            answer = 0
            break
        answer += temp if (w == ')' and stack[-1] == '(' and word[i - 1] == '(') or (
                w == ']' and stack[-1] == '[' and word[i - 1] == '[') else 0
        temp //= 2 if w == ')' else 3
        stack.pop()

if stack:
    print(0)
else:
    print(answer)