import sys

n, myScore, p = map(int, sys.stdin.readline().split())  # 0<=n<=p
if n == 0:
    print(1)
else:
    data = list(map(int, sys.stdin.readline().split()))
    data.sort(reverse=True)  # 내림차순 정렬
    if n == p and data[-1] >= myScore:  # 리스트 꽉 차있고 내 점수 못들어갈 때
        print(-1)
    else:
        rank = n + 1  # 일단 제일 마지막 등수로 넣어놓고
        for i in range(n):  # 리스트 돌면서
            if data[i] <= myScore:  # 내 점수가 더 높거나 같으면
                rank = i + 1  # 그 등수로 갱신
                break
        print(rank)
