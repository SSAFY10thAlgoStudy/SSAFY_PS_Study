import sys


# 일단 먼저 됐는지 체크해보고 안됐으면 안된 열에 대해서만 백트래킹
# 재귀로 맨 처음 넣어보고 다음 넣어보고 그거 취소하고 하면서 k개 다 될때까지 세줌
# idx를 매개변수로 받아서 그게 원래 저장되어있던 값(k개 다 됐을때)보다 커지면 return해줌

def check():  # k개 다 완료 됐는지 체크하는 함수
    for i in range(W):  # 각 col 다 돌면서
        cnt = 1  # 같은거 개수 세는 변수
        for j in range(D - 1):
            if data[j][i] == data[j + 1][i]:  # 나랑 다음거랑 같으면
                cnt += 1  # 하나 늘려주고
            else:  # 다르면
                cnt = 1  # 초기화
            if cnt == K:  # k개 다 됐으면 끝
                break
        if cnt < K:  # K개보다 적으면 실패니까 딴거 볼필요 없음
            return False
    return True


def back(idx, x, lim):  # idx:바꿀 층 개수, x번째층까지 봄, lim개 바꿀거임
    global result
    if idx >= result:  # D개 이상으로 못바꾸니까
        return
    if idx == lim:  # 선택할 개수에 다다르면
        if check():  # 완료됐는지 체크 후
            if idx < result:  # 최소일 경우
                result = idx  # 정답 갱신
                return
    for i in range(x, D):  # x층 부터 보면서
        for j in range(2):  # a, b 약
            tmp = data[i]  # 원복 위해 저장
            data[i] = [j] * W  # i번째 층을 j로 채움
            back(idx + 1, i + 1, lim)  # 재귀
            data[i] = tmp  # 원복


T = int(sys.stdin.readline().strip())
for t in range(1, T + 1):
    D, W, K = map(int, sys.stdin.readline().split())
    data = [list(map(int, sys.stdin.readline().split())) for _ in range(D)]
    if check():  # 기존 상태로도 통과하면
        result = 0  # 할 필요 없음
    else:
        result = K  # k개 넣으면 바뀌니까 이게 최대
        for i in range(1, D + 1):
            back(0, 0, i)
            if result < K:  # 최소만 구하니까 갱신됐으면 끝냄
                break
    print("#{} {}".format(t, result))
