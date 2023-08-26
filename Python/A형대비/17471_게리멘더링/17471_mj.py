import sys
from collections import deque
from itertools import combinations

n = int(sys.stdin.readline().strip())
population = [0] + list(map(int, sys.stdin.readline().split()))
area = [[] for _ in range(n + 1)]

for i in range(1, n + 1):
    tmp = list(map(int, sys.stdin.readline().split()))
    area[i].extend(tmp[1:])


def bfs(cand):  # 입력 받은 게 연결 되어 있는지 확인
    visited = [False for _ in range(len(cand))]  # 입력 받은 배열 방문 확인
    r = cand[0]  # 그냥 맨 처음 요소로 찾아줌
    visited[0] = True  # 맨 처음 방문 처리
    queue = deque([r])  # bfs 위한 큐
    while queue:
        u = queue.popleft()
        for elt in area[u]:  # u와 연결된 것 중에
            if elt in cand:  # 입력 받은 배열 안에 있고
                idx = cand.index(elt)  # 배열에서의 인덱스
                if not visited[idx]:  # 방문하지 않았으면
                    visited[idx] = True  # 방문 처리
                    queue.append(elt)  # 큐에 넣어줌
    if all(visited):  # 전부 방문했으면
        return True
    return False


combination = []
for i in range(1, n//2+1):  # 1개 이상 n개 미만으로 만들 수 있는 모든 조합
    combination.extend(list(combinations(range(1, n + 1), i)))

result = 10e9
for comb in combination:  # 조합에 대해
    other = list(range(1, n + 1))  # 차집합 구하기
    for c in comb:  # 조합 원소 대해
        if c in other:  # 안 지운 거면
            other.remove(c)  # 지워주기
    if bfs(list(comb)) and bfs(other):  # 둘다 다 연결 되어있으면
        a, b = 0, 0  # 각각 인구수 더해줄 변수
        for c in comb:  # 1구역의 인구수 합
            a += population[c]
        for o in other:  # 2구역의 인구수 합
            b += population[o]
        result = min(result, abs(a - b))  # 정답 갱신

if result == 10e9:  # 두개로 나눌 수 없을 때
    print(-1)
else:
    print(result)
