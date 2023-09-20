import sys


def partition(seq, start, end):
    # pivot을 기준으로 pivot보다 작은 원소는 왼쪽으로, 큰 원소는 오른쪽으로 자리 바꿔준 후 pivot의 위치를 반환하는 함수
    pivot = seq[end]  # 편의상 그냥 맨 마지막 값 기준
    pt = start
    for j in range(start, end):  # end-1까지 돌면서
        if seq[j] <= pivot:  # 만약 기준값보다 작거나 같으면
            seq[pt], seq[j] = seq[j], seq[pt]  # j랑 맨 앞부터 차례대로 자리 바꿔서 채워줌
            pt += 1  # 그 다음으로 채울 위치
    seq[pt], seq[end] = seq[end], seq[pt]  # pivot 옮겨주기
    return pt  # pivot의 위치 return


def quickSort(seq, start, end):  # 분할정복 사용
    if start < end:  # 정렬 다 될때까지
        pivot = partition(seq, start, end)  # pivot의 위치 받아서
        quickSort(seq, start, pivot - 1)  # 왼쪽 정렬하고
        quickSort(seq, pivot + 1, end)  # 오른쪽 정렬하고


n, m = map(int, sys.stdin.readline().split())
data = [int(sys.stdin.readline().strip()) for _ in range(n)]

quickSort(data, 0, n - 1)

start, end = 0, 0
result = max(data) - min(data)

while start <= end:  # 포인터 엇갈리기 전까지
    if data[end] - data[start] < m:  # 만약 차이가 m보다 작고
        if end < n - 1:  # end가 맨 끝에 안왔으면
            end += 1  # end 증가
        else:  # end가 맨끝이면
            start += 1  # start를 증가
    elif data[end] - data[start] > m:  # 차이가 m보다 커졌으면
        result = min(result, data[end] - data[start])  # 결과 갱신하고
        start += 1  # start 증가
    else:  # 차이가 m이 된게 최소니까
        result = data[end] - data[start]  # 결과 갱신하고
        break  # 바로 종료

print(result)
