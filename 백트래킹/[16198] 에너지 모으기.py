import sys


def bt(total):
    global answer
    # 종료 구간
    # 구슬을 제거하다 끝과 첫 구슬은 제거할 수 없기 때문에 종료 조건은 LEN 길이가 2
    if len(e) == 2:
        answer = max(answer, total)
    # pop index 고려해서 len() 사용
    for i in range(1, len(e) - 1):
        # e 배열 i index 위치 후에 pop 할거기 때문에 미리 energy 계산
        energy = e[i - 1] * e[i + 1]
        # pop(i) -> i 번째 자리 제거 후에 다시 넣어줄거기 때문에 temp에 저장
        temp = e.pop(i)
        bt(total + energy)
        # 다시 원래 i 번째 자리에 temp 저장
        e.insert(i, temp)


N = int(sys.stdin.readline())
e = list(map(int, sys.stdin.readline().split()))
answer = float('-inf')
bt(0)
print(answer)