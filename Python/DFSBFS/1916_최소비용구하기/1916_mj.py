import sys, heapq

n = int(sys.stdin.readline().strip())
m = int(sys.stdin.readline().strip())
graph = [[] for _ in range(n + 1)]
for _ in range(m):
    a, b, c = map(int, sys.stdin.readline().split())
    graph[a].append([b, c])
start, end = map(int, sys.stdin.readline().split())

INF = 10e9


def dijkstra(start):
    queue = []
    distance = [INF for _ in range(n + 1)]  # 각 정점까지 가는 비용 저장
    heapq.heappush(queue, [start, 0])
    distance[start] = 0  # 맨 처음 위치는 비용 0
    while queue:
        now, dist = heapq.heappop(queue)
        if dist > distance[now]:  # 만약 now에 저장된 비용보다 더 크면
            continue  # 어차피 최소 될 수 없으니까 뛰어넘음(이거 없으면 시간초과 났음)
        for node, cost in graph[now]:  # 연결된 정점에 대해
            next_dist = dist + cost  # 거기까지 가는 비용 계산
            if distance[node] > next_dist:  # 최소비용이면
                distance[node] = next_dist  # 비용 갱신
                heapq.heappush(queue, [node, next_dist])
    return distance  # start에서 다른 정점들까지 가는 비용 저장됨


print(dijkstra(start)[end])
