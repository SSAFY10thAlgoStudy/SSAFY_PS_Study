import sys

n = int(sys.stdin.readline().strip())
data = list(map(int, sys.stdin.readline().split()))
visited = [False for _ in range(n)]
result = []


def back(cnt, energy):
    if cnt == n - 2:  # 맨 앞, 맨 뒤 빼고 다 탐색 완료 했을 때
        result.append(energy)
        return
    for i in range(1, n - 1):
        if not visited[i]:
            left, right = i - 1, i + 1
            if visited[left]:  # 왼쪽 간적 있으면
                while left > 0:  # 내 왼쪽 탐색하면서 간적 없는 곳 처음으로 언제 나오는지 찾음
                    if visited[left]:
                        left -= 1
                    else:
                        break
            if visited[right]:
                while right < n:  # 내 오른쪽 탐색
                    if visited[right]:
                        right += 1
                    else:
                        break
            tmp = energy + (data[left] * data[right])
            visited[i] = True
            back(cnt + 1, tmp)
            visited[i] = False


back(0, 0)
print(max(result))

# 시작 위치 받음
# - 해당 위치에서 양옆거 곱해서 더하고 해당위치 방문처리
# - 만약 바로 양옆이 둘다 방문 한거면 방문 안한 점 나올때까지 인덱스 더하고 빼주기
# - 그 다음 방문 안한 곳에서 똑같은 처리 반복(재귀 활용)
# - 그렇게 양 끝 제외 모든 점을 방문 했으면 전부 더한 값 return
# - 양 끝 제외 모든 점에서 위 작업 반복해서 return 값 리스트에 넣고 최대값 출력
