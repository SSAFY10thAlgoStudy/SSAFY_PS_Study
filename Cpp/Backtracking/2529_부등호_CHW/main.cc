#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

#define MAX 10

int k;
vector<char> oper;
int operand[MAX];
bool used[MAX];

bool printMax = false;
bool printMin = false;

void selectMaxOperand(int remain, int lastVal)
{
    if (printMax)
        return;

    if (remain == 0)
    {
        printMax = true;
        for (int i = 0; i <= k; i++)
        {
            cout << operand[i];
        }
        cout << "\n";
    }
    else if (!printMax)
    {
        for (int i = 9; i >= 0; i--)
        {
            if (!used[i])
            {
                if (oper[k - remain] == '>')
                {
                    if (lastVal > i)
                    {
                        used[i] = true;
                        operand[k - remain + 1] = i;
                        selectMaxOperand(remain - 1, i);
                        used[i] = false;
                    }
                }
                else
                {
                    if (lastVal < i)
                    {
                        used[i] = true;
                        operand[k - remain + 1] = i;
                        selectMaxOperand(remain - 1, i);
                        used[i] = false;
                    }
                }
            }
        }
    }
}

void selectMinOperand(int remain, int lastVal)
{
    if (printMin)
        return;

    if (remain == 0)
    {
        printMin = true;
        for (int i = 0; i <= k; i++)
        {
            cout << operand[i];
        }
        cout << "\n";
    }
    else if (!printMin)
    {
        for (int i = 0; i <= 9; i++)
        {
            if (!used[i])
            {
                if (oper[k - remain] == '>')
                {
                    if (lastVal > i)
                    {
                        used[i] = true;
                        operand[k - remain + 1] = i;
                        selectMinOperand(remain - 1, i);
                        used[i] = false;
                    }
                }
                else
                {
                    if (lastVal < i)
                    {
                        used[i] = true;
                        operand[k - remain + 1] = i;
                        selectMinOperand(remain - 1, i);
                        used[i] = false;
                    }
                }
            }
        }
    }
}

int main(void)
{
    fill_n(&operand[0], MAX, -1);
    fill_n(&used[0], MAX, false);

    cin >> k;

    oper.resize(k);
    for (int i = 0; i < k; i++)
    {
        cin >> oper.at(i);
    }

    for (int i = 9; i >= 0; i--)
    {
        used[i] = true;
        operand[0] = i;
        selectMaxOperand(k, i);
        used[i] = false;
    }

    for (int i = 0; i <= 9; i++)
    {
        used[i] = true;
        operand[0] = i;
        selectMinOperand(k, i);
        used[i] = false;
    }

    return 0;
}