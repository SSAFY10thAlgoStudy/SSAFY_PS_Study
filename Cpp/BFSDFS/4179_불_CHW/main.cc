#include <iostream>
#include <queue>
using namespace std;

int C, R;
char maze[1002][1002];
pair<int, int> cur;
vector<pair<int, int>> fire;
int timeSpent = 0;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

bool isIn(int y, int x)
{
    return 0 < y && y <= R && 0 < x && x <= C;
}

int findEscapeTiming()
{
    queue<pair<int, pair<int, int>>> human;
    queue<pair<int, pair<int, int>>> fireSpread;

    human.push({0, cur});
    for (int i = 0; i < fire.size(); i++)
        fireSpread.push({0, fire.at(i)});
    while (true)
    {
        while (true)
        {
            if (human.size() == 0) // 더 이상 갈 곳이 없는 경우
                return -1;

            auto curHuman = human.front();
            if (curHuman.first == timeSpent) // 현재 시간과 동일하다면 계속 움직이기
            {
                human.pop();

                if (maze[curHuman.second.first][curHuman.second.second] == 'F')
                    continue;

                for (int dir = 0; dir < 4; dir++)
                {
                    int ny = curHuman.second.first + dy[dir];
                    int nx = curHuman.second.second + dx[dir];

                    if (!isIn(ny, nx))
                    {
                        return curHuman.first + 1;
                    }
                    else
                    {
                        if (maze[ny][nx] == '.')
                        {
                            maze[ny][nx] = 'J';
                            human.push({curHuman.first + 1, {ny, nx}});
                        }
                    }
                }
            }
            else
            {
                break;
            }
        }

        while (true)
        {
            if (fireSpread.size() == 0)
                break;
            auto curFire = fireSpread.front();
            if (curFire.first == timeSpent) // 현재 시간과 동일하다면 계속 움직이기
            {
                fireSpread.pop();

                for (int dir = 0; dir < 4; dir++)
                {
                    int ny = curFire.second.first + dy[dir];
                    int nx = curFire.second.second + dx[dir];

                    if (isIn(ny, nx))
                    {
                        if (maze[ny][nx] == '.' || maze[ny][nx] == 'J')
                        {
                            maze[ny][nx] = 'F';
                            fireSpread.push({timeSpent + 1, {ny, nx}});
                        }
                    }
                }
            }
            else
            {
                break;
            }
        }

        timeSpent++;
    }

    return -1;
}
int main(void)
{
    cin >> R >> C;

    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            cin >> maze[i][j];
            if (maze[i][j] == 'J')
            {
                cur.first = i;
                cur.second = j;
            }

            if (maze[i][j] == 'F')
            {
                fire.push_back({i, j});
            }
        }
    }

    int ret = findEscapeTiming();

    if (ret < 0)
        cout << "IMPOSSIBLE";
    else
        cout << ret;

    return 0;
}