#include <iostream>
#include <stack>
#include <vector>
using namespace std;

char sudoku[10][10];
int vertical[10];
int horizontal[10];
int inBound[10];
vector<pair<int, pair<int, int>>> emptyCoord;
bool isFinished = false;

int calcInBound(int y, int x)
{
    return ((y - 1) / 3) * 3 + ((x - 1) / 3) + 1;
}

bool isDuplicated(int y, int x, int val)
{
    int bitVal = (1 << (val - 1));
    if ((bitVal & horizontal[y]) | (bitVal & vertical[x]) | (bitVal & inBound[calcInBound(y, x)]))
        return true;
    return false;
}

void printSudoku()
{
    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            cout << sudoku[i][j];
        }
        cout << "\n";
    }
}

void findCombination(int remaining)
{
    if (isFinished)
        return;
    if (remaining == 0)
    {
        isFinished = true;
        for (int i = 0; i < emptyCoord.size(); i++)
        {
            int y = emptyCoord[i].second.first;
            int x = emptyCoord[i].second.second;
            int val = emptyCoord[i].first;

            sudoku[y][x] = (char)('0' + val);
        }
        printSudoku();

        return;
    }
    else
    {
        pair<int, pair<int, int>> curCoord = emptyCoord[emptyCoord.size() - remaining];
        int y = curCoord.second.first;
        int x = curCoord.second.second;
        // int val = curCoord.first;

        int ret = horizontal[y] | vertical[x] | inBound[calcInBound(y, x)];
        for (int val = 1; val < 10; val++)
        {
            if (isDuplicated(y, x, val))
            {
                continue;
            }
            else
            {
                sudoku[y][x] = (char)('0' + val);
                horizontal[y] |= 1 << (val - 1);
                vertical[x] |= 1 << (val - 1);
                inBound[calcInBound(y, x)] |= 1 << (val - 1);
                emptyCoord[emptyCoord.size() - remaining].first = val;
                findCombination(remaining - 1);
                sudoku[y][x] = '0';
                horizontal[y] -= 1 << (val - 1);
                vertical[x] -= 1 << (val - 1);
                inBound[calcInBound(y, x)] -= 1 << (val - 1);
                emptyCoord[emptyCoord.size() - remaining].first = 0;
            }
        }
    }
}

int main(void)
{
    fill_n(&vertical[0], 10, 0);
    fill_n(&horizontal[0], 10, 0);
    fill_n(&inBound[0], 10, 0);

    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            cin >> sudoku[i][j];
            if (sudoku[i][j] != '0')
            {
                horizontal[i] |= (1 << ((int)(sudoku[i][j] - '0') - 1));
                vertical[j] |= (1 << ((int)(sudoku[i][j] - '0') - 1));
                inBound[calcInBound(i, j)] |= (1 << ((int)(sudoku[i][j] - '0') - 1));
            }
            else
            {
                emptyCoord.push_back({0, {i, j}});
            }
        }
    }

    findCombination(emptyCoord.size());

    return 0;
}