#include <iostream>
using namespace std;

int N, M, T, u, v;
bool graph[21][21], visited[21];
int answer;

void dfs(int cnt, int i)
{
    if (cnt > answer)
        answer = cnt;

    for (int j = 1; j <= N; j++)
    {
        if (!visited[j] && graph[i][j])
        {
            visited[j] = true;
            dfs(cnt + 1, j);
            visited[j] = false;
        }
    }
}

int main(void)
{
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> M;
        fill_n(&graph[0][0], 21 * 21, false);
        fill_n(&visited[0], 21, false);

        for (int i = 0; i < M; i++)
        {
            cin >> u >> v;
            graph[u][v] = graph[v][u] = true;
        }

        answer = 0;

        for (int i = 1; i <= N; i++)
        {
            visited[i] = true;
            dfs(1, i);
            visited[i] = false;
        }

        cout << "#" << t << " " << answer << "\n";
    }
}