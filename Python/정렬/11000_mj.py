import heapq
import sys

# N이 200,000이라 그런지 시간초과
sys.setrecursionlimit(10**9)


def partition(seq, start, end):
    # pivot을 기준으로 pivot보다 작은 원소는 왼쪽으로, 큰 원소는 오른쪽으로 자리 바꿔준 후 pivot의 위치를 반환하는 함수
    pivot = seq[end][0]  # 맨 마지막 값의 첫번째 원소를 기준으로 정렬
    pt = start
    for j in range(start, end):  # end-1까지 돌면서
        if seq[j][0] <= pivot:  # 만약 기준값보다 작거나 같으면
            seq[pt], seq[j] = seq[j], seq[pt]  # j랑 맨 앞부터 차례대로 자리 바꿔서 채워줌
            pt += 1  # 그 다음으로 채울 위치
    seq[pt], seq[end] = seq[end], seq[pt]  # pivot 옮겨주기
    return pt  # pivot의 위치 return


def quickSort(seq, start, end):  # 분할정복 사용
    if start < end:  # 정렬 다 될때까지
        pivot = partition(seq, start, end)  # pivot의 위치 받아서
        quickSort(seq, start, pivot - 1)  # 왼쪽 정렬하고
        quickSort(seq, pivot + 1, end)  # 오른쪽 정렬하고


n = int(sys.stdin.readline().strip())
data = [list(map(int, sys.stdin.readline().split())) for _ in range(n)]

quickSort(data, 0, n - 1)
# data.sort()하면 시간초과 안남

result = []
heapq.heappush(result, data[0][1])  # 맨 처음 수업 끝나는 시간 넣고
for i in range(1, n):  # 그 다음 수업부터 돌면서
    if result[0] > data[i][0]:  # 이전 수업 끝나는 시간보다 지금 수업 시작시간이 빠르면
        heapq.heappush(result, data[i][1])  # 새로운 강의실 필요하니까 PQ에 추가
    else:  # 수업 들을 수 있으면
        heapq.heappop(result)  # 새로운 시간으로 갱신 위해 pop하고
        heapq.heappush(result, data[i][1])  # 다음 시간 넣어줌

print(len(result))
