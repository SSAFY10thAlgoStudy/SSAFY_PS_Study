#include <iostream>
#include <string>
#include <map>
using namespace std;

string oper;
int N;
pair<int, int> king, stone;

// 상하좌우 (direction)
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
map<string, int> direction = {{"T", 0}, {"B", 1}, {"L", 2}, {"R", 3}};

// 좌상, 좌하, 우상, 우하 대각선 (cross direction)
int cdx[] = {-1, -1, 1, 1};
int cdy[] = {1, -1, 1, -1};
map<string, int> crossDirection = {{"LT", 0}, {"LB", 1}, {"RT", 2}, {"RB", 3}};

// 내부 좌표값 판별
bool isIn(int x, int y)
{
    return 0 <= x && x < 8 && 0 <= y && y < 8;
}

// 좌표 문자열 반환
string toString()
{

    string res = "";
    res += char('A' + king.first);
    res += to_string(king.second + 1);
    res += "\n";
    res += char('A' + stone.first);
    res += to_string(stone.second + 1);

    return res;
}

int main(void)
{
    cin >> oper;

    // 인덱스 (0,0)을 좌하단 좌표로 설정
    king.first = oper.at(0) - 'A';
    king.second = oper.at(1) - '1';

    cin >> oper;
    stone.first = oper.at(0) - 'A';
    stone.second = oper.at(1) - '1';

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> oper;
        if (oper.size() == 1)
        {
            // 방향
            int d = direction[oper];
            int nx = king.first + dx[d];
            int ny = king.second + dy[d];

            if (isIn(nx, ny)) // 킹 체스말이 이동 가능한 경우
            {
                if (nx == stone.first && ny == stone.second) // 킹이 이동 시 돌과 겹치는 경우
                {
                    if (isIn(stone.first + dx[d], stone.second + dy[d])) // 돌 또한 이동 가능 한 경우
                    {
                        // 좌표 값 업데이트
                        king.first = nx;
                        king.second = ny;
                        stone.first = nx + dx[d];
                        stone.second = ny + dy[d];
                    }
                    else
                    {
                        continue;
                    }
                }
                else // 킹은 이동 가능하나 돌은 이동 불가
                {
                    king.first = nx;
                    king.second = ny;
                }
            }
            else // 킹이 이동 불가한 경우 아무것도 하지 않고 넘어가기
            {
                continue;
            }
        }
        else
        {
            // 대각선 방향
            int cD = crossDirection[oper];
            int nx = king.first + cdx[cD];
            int ny = king.second + cdy[cD];

            if (isIn(nx, ny)) // 킹이 이동 가능한 경우
            {
                if (nx == stone.first && ny == stone.second) // 킹 이동 시 돌과 겹치는 경우
                {
                    if (isIn(stone.first + cdx[cD], stone.second + cdy[cD])) // 돌 또한 이동 가능한 경우
                    {
                        // 좌표 업데이트
                        king.first = nx;
                        king.second = ny;
                        stone.first = nx + cdx[cD];
                        stone.second = ny + cdy[cD];
                    }
                }
                else // 돌은 이동 불가한 경우 킹만 이동하기
                {
                    king.first = nx;
                    king.second = ny;
                }
            }
            else // 킹이 이동 불가한 경우 생략하기
            {
                continue;
            }
        }
    }

    // 좌표 값 문자열 출력
    cout << toString();
    return 0;
}