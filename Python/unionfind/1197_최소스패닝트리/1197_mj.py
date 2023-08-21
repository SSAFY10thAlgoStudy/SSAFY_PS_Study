# https://www.acmicpc.net/problem/1197
import sys


def find_root(tree, x):
    if tree[x] != x:  # x가 루트노드가 아니라면
        tree[x] = find_root(tree, tree[x])  # 부모의 루트로 바꿔가며 호출
    return tree[x]


def union_set(tree, x, y):
    # 루트노드를 찾아서 루트노드를 같게 바꿔줌
    x = find_root(tree, x)
    y = find_root(tree, y)
    if x <= y:
        tree[y] = x
    else:
        tree[x] = y


v, e = map(int, sys.stdin.readline().split())
graph = []
parent = [i for i in range(v + 1)]  # 자기 자신을 부모로 초기설정

for _ in range(e):
    a, b, c = map(int, sys.stdin.readline().split())
    graph.append([a, b, c])
graph.sort(key=lambda x: x[-1]) # 마지막 원소(비용)로 정렬

total_cost = 0 # 전체 가중치 더할 변수

# 크루스칼 알고리즘
# 비용 낮은 순서로 정렬 후 간선 정보 확인하며 싸이클 여부 확인
# 싸이클 발생하지 않으면 최소신장트리에 포함시키며 트리 만드는 알고리즘

for i in range(e):
    a, b, cost = graph[i]
    # 만약 root가 같으면 싸이클이 생기므로 같지 않은 노드에 대하여
    if find_root(parent, a) != find_root(parent, b):
        union_set(parent, a, b)  # 합쳐주고
        total_cost += cost  # cost추가
print(total_cost)
