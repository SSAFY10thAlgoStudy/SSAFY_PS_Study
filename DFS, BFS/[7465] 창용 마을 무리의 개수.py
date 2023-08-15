def find(a):
    if a != p[a]:
        p[a] = find(p[a])
    return p[a]


def union(a, b):
    a = find(a)
    b = find(b)
    if a > b:
        p[a] = b
    else:
        p[b] = a


for t in range(int(input())):
    n, m = map(int, input().split())
    rs = [list(map(int, input().split())) for _ in range(m)]
    p = [_ for _ in range(n + 1)]
    for r in rs:
        a, b = r
        union(a, b)
    res = 0
    for i in range(1, n + 1):
        if p[i] == i:
            res += 1
    print(f'#{t + 1} {res}')
