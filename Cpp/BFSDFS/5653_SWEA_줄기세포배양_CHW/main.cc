#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

struct cell
{
    int x;
    int y;
    int X;
    int t;
};

struct cmp
{
    bool operator()(cell a, cell b)
    {
        return a.X < b.X;
    }
};

int main(int argc, char **argv)
{
    int test_case, i, j, a, dead, len, x, y, X, nx, ny;
    int T, N, M, K;
    int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int map[350][350];
    vector<cell> cells;
    priority_queue<cell, vector<cell>, cmp> activation;

    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> M >> K;
        memset(map, 0, sizeof(map));
        cells.clear();
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                cin >> a;
                map[150 + i][150 + j] = a;
                if (a != 0)
                    cells.push_back({150 + i, 150 + j, a, a});
            }
        }

        dead = 0;
        len = cells.size();
        while (K > 0)
        {
            K--;
            for (i = 0; i < len; i++)
            {
                cells[i].t--;
                if (cells[i].t == -1)
                { // 비활성화 -> 활성화
                    activation.push(cells[i]);
                }
                if (cells[i].t == -cells[i].X)
                { // 활성화 -> 죽음
                    dead++;
                }
            }

            while (!activation.empty())
            {
                x = activation.top().x, y = activation.top().y, X = activation.top().X, activation.pop();
                for (i = 0; i < 4; i++)
                {
                    nx = x + dir[i][0], ny = y + dir[i][1];
                    if (map[nx][ny] == 0)
                    {
                        map[nx][ny] = X;
                        cells.push_back({nx, ny, X, X});
                        len++;
                    }
                }
            }
        }

        cout << "#" << test_case << " " << len - dead << "\n";
    }
    return 0;
}