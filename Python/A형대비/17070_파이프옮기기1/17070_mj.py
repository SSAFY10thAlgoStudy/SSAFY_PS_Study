import sys

N = int(sys.stdin.readline().strip())

data = [list(map(int, sys.stdin.readline().split())) for _ in range(N)]

dp = [[[0, 0, 0] for _ in range(N)] for _ in range(N)]  # (i, j)에 도착하는 방법의 수를 저장하는 배열
# 가로 세로 대각선

for i in range(1, N):  # 첫 행 보면서
    if data[0][i] == 0:  # 첫 행에 가로로 놓을 수 있으면
        dp[0][i] = [1, 0, 0]  # 가로로 밀면서 놓고
    else:  # 벽 만나면
        break  # 그 다음은 다 가로로 못놓으니까 끝냄

# 첫 행, 열은 어차피 못가니까 (1, 1)부터 시작해도 됨
for i in range(1, N):
    for j in range(1, N):
        if data[i][j] == 0:  # 지금 현재 칸에 파이프 놓을 수 있으면
            dp[i][j][0] = dp[i][j - 1][0] + dp[i][j - 1][2]  # 여기에 놓이는 파이프가 가로일때
            dp[i][j][1] = dp[i - 1][j][1] + dp[i - 1][j][2]  # 세로일때
            if data[i - 1][j] == 0 and data[i][j - 1] == 0:  # 대각선일때
                dp[i][j][2] = dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1] + dp[i - 1][j - 1][2]

print(sum(dp[N-1][N-1]))  # (N, N)에 도착하는 가로세로대각선 수 전부 더해주면됨
