#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 101

int N;
int area[MAX][MAX], test[MAX][MAX];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

bool isIn(int y, int x)
{
    return (0 < y && y <= N) && (0 < x && x <= N);
}

int main(void)
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> area[i][j];
        }
    }

    int max_depth = *max_element(&(area[0][0]), &(area[MAX][MAX]));

    int answer = 1;
    for (int depth = 1; depth < max_depth; depth++)
    {
        queue<pair<int, int>> q;
        int answerTmp = 0;

        copy(&(area[0][0]), &(area[0][0]) + MAX * MAX, &(test[0][0]));

        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                if (test[i][j] > depth)
                {
                    q.push({i, j});
                    test[i][j] = 0;
                    answerTmp++;

                    while (!q.empty())
                    {
                        auto elem = q.front();
                        q.pop();
                        int curY = elem.first;
                        int curX = elem.second;

                        for (int d = 0; d < 4; d++)
                        {
                            int nextY = curY + dy[d];
                            int nextX = curX + dx[d];

                            if (isIn(nextY, nextX) && test[nextY][nextX] > depth)
                            {
                                test[nextY][nextX] = 0;
                                q.push({nextY, nextX});
                            }
                        }
                    }
                }
            }
        }

        if (answerTmp > answer)
        {
            answer = answerTmp;
        }
    }

    cout << answer;

    return 0;
}