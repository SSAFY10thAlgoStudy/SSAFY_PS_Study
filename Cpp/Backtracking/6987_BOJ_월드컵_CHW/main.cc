#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 승패무를 저장하기 위한 구조체
typedef struct GameData
{
    int win;
    int lose;
    int tie;

    GameData(int win, int tie, int lose)
    {
        this->win = win;
        this->lose = lose;
        this->tie = tie;
    }
} GameData;

void solve();
void input();
void search(int turn); // 각 턴 별 가능성을 탐색하는 노드 분기

// 백트래킹을 위한 대결 구도 한정
pair<int, int> competition[15] = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 3}, {2, 4}, {2, 5}, {3, 4}, {3, 5}, {4, 5}};
vector<GameData> result;
bool answer;

void solve()
{
    for (int i = 0; i < 4; i++)
    {
        answer = false;
        input();
        search(0);

        if (answer)
        {
            cout << "1 ";
        }
        else
        {
            cout << "0 ";
        }
    }
}

void input()
{
    int w, t, l;
    result.clear();

    for (int j = 0; j < 6; j++)
    {
        cin >> w >> t >> l;
        result.push_back(GameData(w, t, l));
    }
}

void search(int turn)
{
    if (answer) // 정답을 찾아냈다면 다음 검색을 수행하지 않아도 된다
        return;

    if (turn == 15)
    {
        bool check = true;
        for (int i = 0; i < 6; i++)
        {
            // 모두 0을 만들지 못하면 실패
            if (result.at(i).win || result.at(i).lose || result.at(i).tie)
            {
                check = false;
            }
        }

        if (check)
            answer = check;
    }
    else
    {
        int teamA = competition[turn].first;
        int teamB = competition[turn].second;

        if (result[teamA].win && result[teamB].lose)
        {
            result[teamA].win--;
            result[teamB].lose--;
            search(turn + 1);
            result[teamA].win++;
            result[teamB].lose++;
        }

        if (result[teamA].lose && result[teamB].win)
        {
            result[teamA].lose--;
            result[teamB].win--;
            search(turn + 1);
            result[teamA].lose++;
            result[teamB].win++;
        }

        if (result[teamA].tie && result[teamB].tie)
        {
            result[teamA].tie--;
            result[teamB].tie--;
            search(turn + 1);
            result[teamA].tie++;
            result[teamB].tie++;
        }
    }
}

int main(void)
{
    solve();
    return 0;
}