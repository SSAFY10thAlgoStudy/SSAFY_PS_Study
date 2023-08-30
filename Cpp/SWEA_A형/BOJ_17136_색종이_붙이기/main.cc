#include <iostream>
using namespace std;

int map[11][11];
int remain[5] = {5, 5, 5, 5, 5};

int answer = 101;

bool isIn(int y, int x);
void backtracking(int cnt, int totalRemain);
void check(int y, int x, int size, int revert);
int cnt = 0;

bool isIn(int y, int x)
{
    return y <= 10 && x <= 10;
}

bool isValid(int y, int x, int size)
{
    for (int i = y; i < y + size; i++)
    {
        for (int j = x; j < x + size; j++)
        {
            if (map[i][j] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

void backtracking(int callCnt, int totalRemain)
{
    if (callCnt >= answer)
    {
        return;
    }

    if (totalRemain == 0)
    {
        int ret = 25;
        for (int i = 0; i < 5; i++)
        {
            ret -= remain[i];
        }

        answer = min(answer, ret);
        return;
    }

    for (int y = 1; y <= 10; y++)
    {
        for (int x = 1; x <= 10; x++)
        {
            if (map[y][x] == 1)
            {
                for (int s = 5; s >= 1; s--)
                {
                    if (remain[s - 1] > 0 && isValid(y, x, s) && isIn(y + s - 1, x + s - 1))
                    {
                        check(y, x, s, 0);
                        remain[s - 1]--;

                        backtracking(callCnt + 1, totalRemain - s * s);

                        remain[s - 1]++;
                        check(y, x, s, 1);
                    }
                }

                return;
            }
        }
    }
}

void check(int y, int x, int size, int revert)
{
    for (int i = y; i < size + y; i++)
    {
        for (int j = x; j < size + x; j++)
        {
            map[i][j] = revert;
        }
    }
}

int main(void)
{
    int cover = 0;
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            cin >> map[i][j];
            if (map[i][j])
                cover++;
        }
    }

    backtracking(0, cover);

    if (answer != 101)
        cout << answer;
    else
        cout << -1;

    return 0;
}