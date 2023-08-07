#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

int M, N, K;
int map[100][100];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
vector<int> answers;

bool isIn(int y, int x)
{
    return 0 <= y && y < N && 0 <= x && x < M;
}

void dfs(int y, int x)
{
    int answer = 0;
    stack<pair<int, int>> st;
    st.push({y, x});
    answer++;

    while (!st.empty())
    {
        auto elem = st.top();
        st.pop();

        int y = elem.first;
        int x = elem.second;
        map[y][x] = 1;

        int ny, nx;
        for (int i = 0; i < 4; i++)
        {
            ny = y + dy[i];
            nx = x + dx[i];

            if (isIn(ny, nx) && map[ny][nx] == 0)
            {
                map[ny][nx] = 1;
                st.push({ny, nx});
                answer++;
            }
        }
    }

    answers.push_back(answer);
}
int main(void)
{
    fill_n(&map[0][0], 100 * 100, false);

    cin >> N >> M >> K;

    int y1, x1, y2, x2;
    for (int i = 0; i < K; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        y1 = M - y1;
        y2 = M - y2;
        x1 = N - x1;
        x2 = N - x2;
        cout << y1 << x1 << " " << y2 << x2 << "\n\n";

        for (int y = y2; y < y1; y++)
        {
            for (int x = x2; x < x1; x++)
            {
                map[y][x] = 1;
            }
        }
    }

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (map[i][j] == 0)
            {
                dfs(i, j);
            }
        }
    }

    sort(answers.begin(), answers.end());

    for (int i = 0; i < answers.size(); i++)
    {
        cout << answers.at(i) << " ";
    }
}