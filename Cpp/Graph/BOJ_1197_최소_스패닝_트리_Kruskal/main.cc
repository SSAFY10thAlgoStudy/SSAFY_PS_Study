#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int V, E, u, v, w, answer = 0;
vector<pair<int, pair<int, int>>> graph;
int parent[10001];

/**
 * 최상위 부모를 찾기 위한 함수
 * 주어진 정점 x에 대한 부모를 재귀적으로 찾아 최상위 부모를 반환
 */
int find_parent(int x)
{
    if (parent[x] == x) // 이미 자기 자신이 최상위 부모라면 자신을 반환한다
        return x;
    return parent[x] = find_parent(parent[x]); // 최상단까지 타고 올라가 값을 반환 + 부모 값을 업데이트
}

/**
 * x와 y의 합집합 연산을 수행한다
 */
void union_parent(int x, int y)
{
    x = find_parent(x); // x의 부모 찾기
    y = find_parent(y); // y의 부모 찾기

    if (x != y) // 다른 집합에 속해있는 경우에만
    {
        if (x < y) // y가 더 큰 경우 작은 x를 부모로 설정한다
        {
            parent[y] = x; // y의 부모를 x로 설정한다 (합집합의 효과와 동일)
        }
        else // x가 더 큰 경우 작은 y를 부모로 설정한다
        {
            parent[x] = y; // x의 부모를 y로 설정한다 (합집합의 효과와 동일)
        }
    }
}

int main()
{
    // 입력 횟수가 많아 시간 초과 방지를 위해 적는다
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V >> E;               // 정점의 수와 간선 갯수를 입력받는다
    for (int i = 1; i <= V; i++) // 모든 정점에 대해
    {
        parent[i] = i; // 최상위 부모 초기화
    }

    for (int i = 0; i < E; i++)
    {
        cin >> u >> v >> w;
        graph.push_back({w, {u, v}}); // 간선을 따라 정렬하기 위해 {간선, {정점A, 정점B}} 형태로 삽입
    }

    sort(graph.begin(), graph.end()); // 간선의 가중치가 가장 작은 것부터 확인하기 위해 정렬

    for (int i = 0; i < E; i++) // 모든 간선에 대해 수행해보기
    {
        if (find_parent(graph[i].second.first) != find_parent(graph[i].second.second)) // u vertex와 v vertex가 다른 부모에 속해있다면
        {
            union_parent(graph[i].second.first, graph[i].second.second); // u vertex와 v vertex 합집합 후
            answer += graph[i].first;                                    // 가중치 합산
        }
    }

    cout << answer << "\n"; // MST spanning을 통해 얻은 간선의 총합을 출력한다
}