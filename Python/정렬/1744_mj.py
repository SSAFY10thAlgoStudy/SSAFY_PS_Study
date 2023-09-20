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


def partitionRev(seq, start, end):
    # pivot을 기준으로 pivot보다 작은 원소는 왼쪽으로, 큰 원소는 오른쪽으로 자리 바꿔준 후 pivot의 위치를 반환하는 함수
    pivot = seq[end]  # 편의상 그냥 맨 마지막 값 기준
    pt = start
    for j in range(start, end):  # end-1까지 돌면서
        if seq[j] >= pivot:  # 만약 기준값보다 작거나 같으면
            seq[pt], seq[j] = seq[j], seq[pt]  # j랑 맨 앞부터 차례대로 자리 바꿔서 채워줌
            pt += 1  # 그 다음으로 채울 위치
    seq[pt], seq[end] = seq[end], seq[pt]  # pivot 옮겨주기
    return pt  # pivot의 위치 return


def quickSort(seq, start, end, order):  # 분할정복 사용
    if order:  # order이 true면 오름차순 정렬
        if start < end:  # 정렬 다 될때까지
            pivot = partition(seq, start, end)  # pivot의 위치 받아서
            quickSort(seq, start, pivot - 1, True)  # 왼쪽 정렬하고
            quickSort(seq, pivot + 1, end, True)  # 오른쪽 정렬하고
    else:  # 내림차순 정렬
        if start < end:  # 정렬 다 될때까지
            pivot = partitionRev(seq, start, end)  # pivot의 위치 받아서
            quickSort(seq, start, pivot - 1, False)  # 왼쪽 정렬하고
            quickSort(seq, pivot + 1, end, False)  # 오른쪽 정렬하고


n = int(sys.stdin.readline().strip())

positive = []  # 1보다 큰 양수 담을 배열
negative = []  # 0, 음수 담을 배열(0이랑 음수 곱해야 커짐)
result = 0  # 결과
for _ in range(n):
    t = int(sys.stdin.readline().strip())
    if t > 1:
        positive.append(t)
    elif t <= 0:
        negative.append(t)
    else:  # 1이면 답에 더해주는게 더 결과 커짐
        result += t

quickSort(positive, 0, len(positive) - 1, False)  # 내림차순 정렬
quickSort(negative, 0, len(negative) - 1, True)  # 오름차순으로 정렬해야 절댓값 큰 순으로 정렬됨

for i in range(0, len(positive), 2):  # 양수 2개씩 묶을거니까
    if i >= len(positive) - 1:  # 맨 마지막이면
        result += positive[i]  # 그냥 더하고
    else:  # 아니면
        result += positive[i] * positive[i + 1]  # 두개씩 곱해서 더해줌

for i in range(0, len(negative), 2):
    if i >= len(negative) - 1:
        result += negative[i]
    else:
        result += negative[i] * negative[i + 1]

print(result)
