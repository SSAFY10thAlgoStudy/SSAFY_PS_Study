#include <iostream>
using namespace std;

int N, M, u, v, w, s, e;
int map[1000][1000], dist[1000];
bool visited[1000];

int nextNode()
{
    int minNode = -1;
    int min = -1;
    for (int i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            if (dist[i] < min)
            {
                min = dist[i];
                minNode = i;
            }
        }
    }

    return minNode;
}

void dijkstra(int start)
{
    for (int i = 0; i < N; i++)
    {
        dist[i] = map[start][i];
    }

    visited[start] = true;
    for (int i = 0; i < N - 1; i++)
    {
        int minNode = nextNode();
        visited[minNode] = true;
        for (int j = 0; j < N; j++)
        {
            if (!visited[j])
            {
                if (dist[minNode] + map[minNode][j] < dist[j])
                {
                    dist[j] = dist[minNode] + map[minNode][j];
                }
            }
        }
    }
}
int main(void)
{
    fill_n(&(map[0][0]), 1000 * 1000, 2e9);
    fill_n(&(dist[0]), 1000, 2e9);

    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        cin >> u >> v >> w;
        u -= 1;
        v -= 1;
        map[u][v] = w;
        map[v][u] = w;
    }

    for (int i = 0; i < N; i++)
    {
        map[i][i] = 0;
    }

    cin >> s >> e;
    dijkstra(s - 1);
    cout << dist[e - 1];

    return 0;
}