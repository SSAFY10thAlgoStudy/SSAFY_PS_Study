Minimum Spanning Tree

Kruskal 알고리즘

1. 간선을 오름차순으로 정렬하고 가장 낮은 비용의 간선을 택한다.
2. 현재 선택한 간선이 정점 u,v를 연결하는 간선일 때, u,v가 같은 그룹에 속할 때만 간선을 최소 신장 트리에 추가할 수 있다.
3. 최소 신장 트리에 (V-1)개의 간선을 추가시켰다면 과정을 종료, 그렇지 않다면 그 다음으로 비용이 작은 간선을 선택 후 2번 과정을 반복한다.

Union & Find 알고리즘을 알고 있어야 구현 가능하다.

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<tuple>
using namespace std;

int V, E, A, B, C;
int u, v, w;
int parent[10001];
long long ans;
bool check;
vector<tuple<int, int, int>> graph;

/**
 * x의 최상위 노드 찾기
 */
int find_parent(int x)
{
	if (parent[x] == x) // 자기자신이 부모일 경우
		return x;
	else // 부모 노드 찾기
		return parent[x] = find_parent(parent[x]);
}

/**
 *
 */
void union_node(int u, int v)
{
	check = false;

	u = find_parent(u);
	v = find_parent(v);

	if (u == v) // 부모가 같다면 결합 시 사이클 이므로 (u,v 사이에 간선이 존재하는데 부모가 같다면 사이클)
		return; // 연결하지 않는다.
	else
	{
		parent[u] = v; // 결합 & 부모로 기록
		check = true;
	}
}

int main()
{
	cin >> V >> E;

	// 부모를 자기 자신으로 초기화
	for (int i = 1; i <= V; i++)
		parent[i] = i;

	// 그래프 정보 저장
	for (int i = 0; i < E; i++)
	{
		cin >> A >> B >> C;
		graph.push_back(make_tuple(C, A, B));
	}

	// 가중치가 작은 간선부터 오름차순으로 정렬
	sort(graph.begin(), graph.end());

	// 간선들 결합 (MST 찾기)
	for (int i = 0; i < E; i++)
	{
		/*
		get<0>(graph[i] : 가중치
		get<1>(graph[i] : 출발 노드
		get<2>(graph[i] : 도착 노드
		*/
		union_node(get<1>(graph[i]), get<2>(graph[i]));

        // 사이클이 안생기는 경우에 한해서 가중치를 더한다.
		if (check) ans += get<0>(graph[i]); // 가중치 더하기
	}

	cout << ans << '\n';
}
```
