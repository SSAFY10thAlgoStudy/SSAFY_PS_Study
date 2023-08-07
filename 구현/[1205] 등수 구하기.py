import bisect
N, score, P = map(int, input().split())
answer = 1
if N:
    rank = sorted(list(map(int, input().split())) + [score])
    r = N + 2 - bisect.bisect_right(rank, score)
    if r > P or N == P and rank[0] == score:
        answer = -1
    else:
        answer = r
print(answer)