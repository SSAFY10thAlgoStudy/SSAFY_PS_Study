import sys

king, stone, n = sys.stdin.readline().split()
n = int(n)

king = list(king)
king[0] = ord(king[0]) - 65
king[1] = int(king[1]) - 1
stone = list(stone)
stone[0] = ord(stone[0]) - 65
stone[1] = int(stone[1]) - 1

cmd = [sys.stdin.readline().strip() for _ in range(n)]

dx = [1, -1, 0, 0, 1, -1, 1, -1]
dy = [0, 0, -1, 1, 1, 1, -1, -1]
idx = {"R": 0, "L": 1, "B": 2, "T": 3, "RT": 4, "LT": 5, "RB": 6, "LB": 7}


for c in cmd:
    kingTmp0, kingTmp1 = king[0] + dx[idx[c]], king[1] + dy[idx[c]]  # 옮길 자리
    if kingTmp0 == stone[0] and kingTmp1 == stone[1]:  # 킹이 옮긴 자리와 돌 자리가 같을 때
        stoneTmp0, stoneTmp1 = stone[0] + dx[idx[c]], stone[1] + dy[idx[c]]  # 돌 옮길 자리
        if 0 <= stoneTmp0 < 8 and 0 <= stoneTmp1 < 8:  # 범위 안에 있으면 옮기기
            stone[0], stone[1] = stoneTmp0, stoneTmp1
        else:
            continue  # 돌이 범위 밖으로 나가면 다음 이동으로
    if 0 <= kingTmp0 < 8 and 0 <= kingTmp1 < 8:  # 범위 안에 있으면 옮기기
        king[0], king[1] = kingTmp0, kingTmp1

king[0] = chr(king[0] + 65)
king[1] = str(king[1] + 1)
stone[0] = chr(stone[0] + 65)
stone[1] = str(stone[1] + 1)
print(king[0] + king[1])
print(stone[0] + stone[1])
