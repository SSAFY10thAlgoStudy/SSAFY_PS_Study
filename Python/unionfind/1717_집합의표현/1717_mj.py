# https://www.acmicpc.net/problem/1717
import sys

sys.setrecursionlimit(10 ** 9)

n, m = map(int, sys.stdin.readline().split())
tree = [i for i in range(n + 1)]  # 자기 자신을 부모로 초기 설정


def find_root(x):
    if tree[x] != x:  # x가 루트노드가 아니라면
        tree[x] = find_root(tree[x])  # 부모의 루트로 바꿔가며 호출
    return tree[x]


def union_set(x, y):
    # 루트노드를 찾아서 루트노드를 같게 바꿔줌
    x = find_root(x)
    y = find_root(y)
    if x <= y:
        tree[y] = x
    else:
        tree[x] = y


for _ in range(m):
    op, a, b = map(int, sys.stdin.readline().split())
    if op == 1:
        if find_root(a) == find_root(b):
            print("yes")
        else:
            print("no")
    else:
        union_set(a, b)
