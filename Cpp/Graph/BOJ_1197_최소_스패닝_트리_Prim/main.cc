#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> pair_ii;

int V, E, A, B, C;
int u, v, w;
long long ans;
bool visit[10001];
vector<pair_ii> graph[10001];
priority_queue<pair_ii, vector<pair_ii>, greater<pair_ii>> pq; // 오름차순 우선순위 큐

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> V >> E;

    // 그래프 연결 정보 저장
    for (int i = 0; i < E; i++)
    {
        cin >> A >> B >> C;
        graph[A].push_back(make_pair(B, C));
        graph[B].push_back(make_pair(A, C));
    }

    pq.push(make_pair(0, 1)); // (가중치, 노드)

    while (!pq.empty())
    {
        int now_weight = pq.top().first;
        int now_node = pq.top().second;

        pq.pop();

        // 이미 방문했으면 넘어감
        if (visit[now_node])
            continue;

        visit[now_node] = true; // 방문 표시

        ans += now_weight;

        // 다음 정점들을 우선순위 큐에 삽입
        for (int i = 0; i < graph[now_node].size(); i++)
        {
            int next_node = graph[now_node][i].first;
            int next_weight = graph[now_node][i].second;

            pq.push(make_pair(next_weight, next_node));
        }
    }
    cout << ans << '\n';
}