def check():
    global D, W, K
    # 세로줄 하나하나 검사 시작
    for w in range(W):
        flag = False
        count = 0
        target = graph[0][w]
        for d in range(D):
            if target == graph[d][w]:
                count += 1
            else:
                count = 0
                target = graph[d][w]
            if count >= K:
                flag = True
                break
        if not flag:
            return False
    return True

def change(d, target):
    global W
    for w in range(W):
        graph[d][w] = target

def bt(start, value):
    global W

    if start == W:
        return
    for w in range(W)


T = int(input())
for testcase in range(1, T+1):
    D, W, K = map(int, input().split())
    graph = [list(map(int, input().split())) for _ in range(D)]
    if K== 1 or check():
        print(0)
    else:

        bt(0)
