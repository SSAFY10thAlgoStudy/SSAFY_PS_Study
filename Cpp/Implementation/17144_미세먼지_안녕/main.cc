#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define MAX 51
int R, C, T;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

// �� �� �� ��
int cy1[] = {-1, 0, 1, 0};
int cx1[] = {0, 1, 0, -1};

// �� �� �� ��
int cy2[] = {1, 0, -1, 0};
int cx2[] = {0, 1, 0, -1};

int map[MAX][MAX];
int copiedMap[MAX][MAX];

typedef struct Dirt
{
    int y, x;
    int amount = 0;

    Dirt(int y, int x)
    {
        this->y = y;
        this->x = x;
    }

    Dirt(int y, int x, int amount)
    {
        this->y = y;
        this->x = x;
        this->amount = amount;
    }
} Dirt;

vector<pair<int, int>> cleaner;
vector<Dirt> dirt;

void printMap();
bool isIn(int y, int x);
int sumOfDirt();
int simulation();
void update();
void spreadDirt();
void cleaning();

void printMap()
{
    cout << "\n\n";
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

bool isIn(int y, int x)
{
    return (1 <= y && y <= R) && (1 <= x && x <= C);
}

/*
    �̼����� ���� ��ȯ
*/
int sumOfDirt()
{
    int sum = 0;
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            if (map[i][j] > 0)
                sum += map[i][j];
        }
    }
    return sum;
}

/*
    �ùķ��̼� ����� ��ȯ�Ѵ�
*/
int simulation()
{
    update();
    return sumOfDirt();
}

/*
    1�ʿ� �ش��ϴ� ������Ʈ�� �����Ѵ�
*/
void update()
{
    while (T--)
    {
        spreadDirt();
        cleaning();
    }
}

/*
    �̼������� Ȯ���Ų��
*/
void spreadDirt()
{
    fill_n(&copiedMap[0][0], MAX * MAX, 0);
    int ny, nx, val, cnt;

    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            if (map[i][j] > 0)
            {
                cnt = 0;
                val = map[i][j];
                copiedMap[i][j] += val;

                for (int d = 0; d < 4; d++)
                {
                    ny = i + dy[d];
                    nx = j + dx[d];

                    if (isIn(ny, nx) && map[ny][nx] >= 0)
                    {
                        copiedMap[ny][nx] += val / 5;
                        cnt++;
                    }
                }

                if (cnt)
                {
                    copiedMap[i][j] -= val / 5 * cnt;
                }
            }
        }
    }

    memcpy(map, copiedMap, sizeof(copiedMap));
}

/*
    ����û���⸦ �����Ѵ�
*/
void cleaning()
{
    int sy1 = cleaner[0].first;
    int sx1 = cleaner[0].second;
    int sy2 = cleaner[1].first;
    int sx2 = cleaner[1].second;

    int y1 = sy1, x1 = sx1, y2 = sy2, x2 = sx2;

    map[sy1][sx1] = 0;
    map[sy2][sx2] = 0;
    int tmp;
    for (int d = 0; d < 4; d++)
    {
        while (1 <= y1 + cy1[d] && y1 + cy1[d] <= sy1 && 1 <= x1 + cx1[d] && x1 + cx1[d] <= C)
        {
            tmp = map[y1][x1];
            map[y1][x1] = map[y1 + cy1[d]][x1 + cx1[d]];
            map[y1 + cy1[d]][x1 + cx1[d]] = tmp;
            y1 = y1 + cy1[d];
            x1 = x1 + cx1[d];
        }

        while (sy2 <= y2 + cy2[d] && y2 + cy2[d] <= R && 1 <= x2 + cx2[d] && x2 + cx2[d] <= C)
        {

            tmp = map[y2][x2];
            map[y2][x2] = map[y2 + cy2[d]][x2 + cx2[d]];
            map[y2 + cy2[d]][x2 + cx2[d]] = tmp;
            y2 = y2 + cy2[d];
            x2 = x2 + cx2[d];
        }
    }

    map[sy1][sx1] = -1;
    map[sy1][sx1 + 1] = 0;
    map[sy2][sx2] = -1;
    map[sy2][sx2 + 1] = 0;
}

int main()
{

    cin >> R >> C >> T;

    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            cin >> map[i][j];
            if (map[i][j] != 0)
            {
                if (map[i][j] > 0)
                {
                    dirt.push_back({i, j, map[i][j]});
                }
                else
                {
                    cleaner.push_back({i, j});
                }
            }
        }
    }

    cout << simulation();
    return 0;
}
