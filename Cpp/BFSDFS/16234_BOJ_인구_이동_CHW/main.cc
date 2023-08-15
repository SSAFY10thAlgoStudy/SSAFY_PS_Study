#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, L, R;
int map[50][50], copiedMap[50][50], mergeData[2500];
bool visited[50][50];
queue<pair<int, int>> q;
vector<pair<int, int>> unionList;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

bool isIn(int y, int x)
{
    return 0 <= y && y < N && 0 <= x && x < N;
}

bool stepMerge()
{
    fill_n(&mergeData[0], 2500, -1);
    fill_n(&visited[0][0], 50 * 50, false);
    bool res = false;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (visited[i][j])
                continue;

            int sum = 0;

            q.push({i, j});
            visited[i][j] = true;
            unionList.clear();

            while (!q.empty())
            {
                auto elem = q.front();
                unionList.push_back({elem.first, elem.second});

                q.pop();

                int numOfPeople = map[elem.first][elem.second];

                sum += numOfPeople;

                for (int d = 0; d < 4; d++)
                {
                    int ny = elem.first + dy[d];
                    int nx = elem.second + dx[d];

                    if (isIn(ny, nx) && !visited[ny][nx])
                    {
                        int diff = abs(numOfPeople - map[ny][nx]);
                        if (L <= diff && diff <= R)
                        {
                            visited[ny][nx] = true;
                            q.push({ny, nx});
                        }
                    }
                }
            }

            if (unionList.size() > 1)
            {
                res = true;
                int unionPopulation = sum / unionList.size();
                for (int k = 0; k < unionList.size(); k++)
                {
                    map[unionList.at(k).first][unionList.at(k).second] = unionPopulation;
                }
            }
        }
    }

    return res;
}

int main(void)
{
    cin >> N >> L >> R;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> map[i][j];
        }
    }

    int day = 0;
    while (stepMerge())
    {
        day++;
    }
    cout << day;
    return 0;
}