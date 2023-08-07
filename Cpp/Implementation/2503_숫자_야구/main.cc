#include <iostream>
using namespace std;

int N;
int num[100], ball[100], strike[100];
int isPossible[1000];

int main(void)
{
    fill_n(&isPossible[0], 1000, 0);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> num[i] >> strike[i] >> ball[i];
    }

    int curStrike, curBall, cnt = 0;

    // 영수가 생각한 n개의 숫자에 대해
    for (int n = 0; n < N; n++)
    {
        int first_digit, second_digit, third_digit;
        first_digit = num[n] / 100;
        second_digit = (num[n] - first_digit * 100) / 10;
        third_digit = (num[n] - first_digit * 100 - 10 * second_digit);
        curStrike = curBall = 0;

        for (int i = 1; i <= 9; i++)
        {
            if (i == first_digit)
                curStrike++;
            if (i == second_digit)
                curBall++;
            if (i == third_digit)
                curBall++;

            for (int j = 1; j <= 9; j++)
            {
                if (i == j)
                    continue;

                if (j == first_digit)
                    curBall++;
                if (j == second_digit)
                    curStrike++;
                if (j == third_digit)
                    curBall++;
                for (int k = 1; k <= 9; k++)
                {
                    if (i == k || j == k)
                        continue;

                    if (k == first_digit)
                        curBall++;
                    if (k == second_digit)
                        curBall++;
                    if (k == third_digit)
                        curStrike++;

                    if (curStrike == strike[n] && curBall == ball[n])
                    {
                        isPossible[i * 100 + j * 10 + k]++;
                    }

                    if (k == first_digit)
                        curBall--;
                    if (k == second_digit)
                        curBall--;
                    if (k == third_digit)
                        curStrike--;
                }
                if (j == first_digit)
                    curBall--;
                if (j == second_digit)
                    curStrike--;
                if (j == third_digit)
                    curBall--;
            }
            if (i == first_digit)
                curStrike--;
            if (i == second_digit)
                curBall--;
            if (i == third_digit)
                curBall--;
        }
    }

    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            if (i == j)
                continue;
            for (int k = 1; k <= 9; k++)
            {
                if (j == k || i == k)
                    continue;

                if (isPossible[i * 100 + j * 10 + k] == N)
                {
                    cnt++;
                }
            }
        }
    }
    cout << cnt;

    return 0;
}