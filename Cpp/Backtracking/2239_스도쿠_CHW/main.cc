#include <iostream>
#include <stack>
#include <vector>
using namespace std;

char sudoku[10][10];	// '1'~'9'�� ���� sudoku ���带 �ǹ��Ѵ�. �ε��� ����� ���̼��� ���� (1,1)���� �����ϵ��� ����
int vertical[10];		// ������ ���� ���� �����ϴ� ���� (vertical[3] => 3�� ���� ��)
int horizontal[10];		// ������ ���� ���� �����ϴ� ���� (horizontal[7] => 7�� ���� ��)
int inBound[10];		// 3x3 ���簢���� �� ���� ��θ� �ε��� 1��, ���� �Ϻθ� �ε��� 9�� ������ ����
vector<pair<int, pair<int, int>>> emptyCoord;	// '0'���� ǥ��� ��ǥ ��ġ�� �����ϴ� ����Ʈ
bool isFinished = false;	// ���� ���� �Ϸ� �÷��� => �� ó�� �ش��� ���ϰ� �÷��װ� �����Ǹ� �� ���Ŀ� ����Ǵ� ��͸� �� �̻� �������� �ʴ´�

/*
��ǥ (y,x)�� �޾� 3x3 ���簢�� ������ �ε��� ��ȯ
*/
int calcInBound(int y, int x)
{
    return ((y - 1) / 3) * 3 + ((x - 1) / 3) + 1;
}

/*
���� �߰��Ϸ��� ��ġ (y,x)�� val�� ���� �� ������ ��Ģ�� �����ϳ� üũ�ϴ� �Լ�
*/
bool isDuplicated(int y, int x, int val)
{
    int bitVal = (1 << (val - 1));	// ��Ʈ �� ��ȯ

	// ��ȯ�� ��Ʈ���� ���� ���� 3x3 3���� ���� ��ġ�� ��찡 �ִٸ� true ��ȯ
    if ((bitVal & horizontal[y]) | (bitVal & vertical[x]) | (bitVal & inBound[calcInBound(y, x)]))
        return true;
    return false;
}

/*
������ ���
*/
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

/*
remaining : �߰������� ���� ��������� �ϴ� ���� emptyCoord ����

���� emptyCoord ������� �ϳ��� ���ο� ���� ä������ ��� ��Ʈ��ŷ�� �����Ѵ�.
*/
void findCombination(int remaining)
{
    if (isFinished)	// �̹� �ش��� ã�� ��� �Լ� ����
        return;

    if (remaining == 0)	// ��� emptyCoord�� ä�� ���
    {
        isFinished = true;	// �ش��� ã�� ���
        printSudoku();

        return;
    }
    else
    {
		// ���� ��ǥ �� �޾ƿ���
        pair<int, pair<int, int>> curCoord = emptyCoord[emptyCoord.size() - remaining];
        int y = curCoord.second.first;
        int x = curCoord.second.second;
        // int val = curCoord.first;

        int ret = horizontal[y] | vertical[x] | inBound[calcInBound(y, x)];
		// 1~9 ������ ����
        for (int val = 1; val < 10; val++)
        {
			// ������ ������ �������� ������ ����
            if (isDuplicated(y, x, val))
            {
                continue;
            }
            else
            {
                sudoku[y][x] = (char)('0' + val);							// ������ �� �ֱ�
                horizontal[y] |= 1 << (val - 1);							// horizontal ����
                vertical[x] |= 1 << (val - 1);								// vertical ����
                inBound[calcInBound(y, x)] |= 1 << (val - 1);				// 3x3 ����
                emptyCoord[emptyCoord.size() - remaining].first = val;		// ���� ���� ��Ȳ ����

                findCombination(remaining - 1);								// ���� �ܰ� ����

                sudoku[y][x] = '0';											// ������ ����
                horizontal[y] -= 1 << (val - 1);							// horizontal ����
                vertical[x] -= 1 << (val - 1);								// vertical ����
                inBound[calcInBound(y, x)] -= 1 << (val - 1);				// 3x3 ����
                emptyCoord[emptyCoord.size() - remaining].first = 0;		// emptyCoord ���� ���� ���� 0���� ����
            }
        }
    }
}

int main(void)
{
	// �ʱ�ȭ
    fill_n(&vertical[0], 10, 0);
    fill_n(&horizontal[0], 10, 0);
    fill_n(&inBound[0], 10, 0);

    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            cin >> sudoku[i][j];	// ������ �Է� �ޱ�
            if (sudoku[i][j] != '0')	// ���ڰ� �Էµ� ��� horizontal, vertical, 3x3�� �ش� �ε����� ������ ������ ���� ���� �������ֱ�
            {
                horizontal[i] |= (1 << ((int)(sudoku[i][j] - '0') - 1));
                vertical[j] |= (1 << ((int)(sudoku[i][j] - '0') - 1));
                inBound[calcInBound(i, j)] |= (1 << ((int)(sudoku[i][j] - '0') - 1));
            }
            else
            {
                emptyCoord.push_back({0, {i, j}});	// �� ��ǥ �߰�
            }
        }
    }

    findCombination(emptyCoord.size());

    return 0;
}