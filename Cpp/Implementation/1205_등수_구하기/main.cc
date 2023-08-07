#include <iostream>
#include <vector>
using namespace std;

int N, newScore, P, tmp;

int main(void)
{
    cin >> N >> newScore >> P;
    vector<int> scores;
    for (int i = 0; i < N; i++)
    {
        cin >> tmp;
        scores.push_back(tmp);
    }

    int grade = 1, cnt = 0;
    for (int i = 0; i < N; i++)
    {
        if (scores[i] > newScore)
        {
            grade++;
        }
        else if (scores[i] == newScore)
        {
            ;
        }
        else
        {
            break;
        }
        cnt++;
    }

    if (cnt == P)
    {
        grade = -1;
    }
    if (N == 0)
    {
        grade = 1;
    }

    cout << grade;

    return 0;
}