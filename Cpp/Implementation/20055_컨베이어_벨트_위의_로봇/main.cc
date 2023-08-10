#include <iostream>
#include <list>
#include <deque>
using namespace std;

// 컨베이어 벨트의 칸을 의미하는 Square 구조체. 내구도와 로봇 포함 여부로 구성됨
typedef struct Square
{
    int durability;
    bool includeRobot;

    Square()
    {
        this->durability = 0;
        this->includeRobot = false;
    }

    Square(int durability)
    {
        this->durability = durability;
        this->includeRobot = false;
    }
} Square;

int N, K, num, numOfZero;
Square *conveyBelt = nullptr, *copiedBelt = nullptr;

// 벨트를 모두 한 칸 씩 이동시킨다. 배열 인덱스 조정을 통해 구현
void moveBelt()
{
    // 벨트 한 칸 씩 움직이기
    for (int i = 1; i < N * 2; i++)
    {
        copiedBelt[i] = conveyBelt[i - 1];
    }
    copiedBelt[0] = conveyBelt[N * 2 - 1];

    // 로봇을 올리는 위치에 도달한 녀석이라면 없애기
    if (copiedBelt[N - 1].includeRobot)
    {
        copiedBelt[N - 1].includeRobot = false;
    }

    // 복사 배열을 통해 원복
    for (int i = 0; i < N * 2; i++)
    {
        conveyBelt[i] = copiedBelt[i];
    }
}

// 이동 가능한 로봇 이동시키기
void moveRobot()
{

    // (N-1)칸의 로봇을 N으로 옮겨 없애기
    if (conveyBelt[N - 2].includeRobot)
    {
        // 내구성이 확보되어 있고 로봇이 위에 있지 않다면
        if (conveyBelt[N - 1].durability && !conveyBelt[N - 1].includeRobot)
        {
            // 내구도를 하나 줄이고 로봇을 옮긴 후 바로 올리기 (includeRobot을 참으로 설정하지 않아도 됨)
            conveyBelt[N - 1].durability--;
            // (N-1) 번째 칸에 있던 로봇은 이제 없다
            conveyBelt[N - 2].includeRobot = false;
        }
    }

    // 1 ~ (N-2) 칸의 로봇에 대해 한 칸 씩 옮길 수 있다면 옮기기
    for (int i = N - 3; i >= 0; i--)
    {
        // 현재 위치에 로봇이 있는 경우 올려보도록 하자
        if (conveyBelt[i].includeRobot)
        {
            // 다음 컨베이어 칸의 내구도 확보가 되어있고, 로봇이 없는 경우
            if (conveyBelt[i + 1].durability && !conveyBelt[i + 1].includeRobot)
            {
                // 내구도를 하나 깎고, 로봇을 한 칸 이동시킨다.
                conveyBelt[i + 1].durability--;
                conveyBelt[i + 1].includeRobot = true;
                conveyBelt[i].includeRobot = false;
            }
        }
    }
}

// 로봇 올려놓기
void putRobot()
{
    if (!conveyBelt[0].includeRobot && conveyBelt[0].durability)
    {
        conveyBelt[0].includeRobot = true;
        conveyBelt[0].durability--;
    }
}

// 내구도 조건을 만족하는지 판별하기
bool isPossible()
{
    // 내구도가 0인 컨베이어 벨트의 갯수가 0이상인지 판별
    numOfZero = 0;
    for (int i = 0; i < N * 2; i++)
    {
        if (conveyBelt[i].durability <= 0)
        {
            numOfZero++;
        }
    }

    if (numOfZero >= K)
    {
        return false;
    }
    return true;
}

// 업데이트 함수
bool cycle()
{
    moveBelt();          // 벨트 이동
    moveRobot();         // 로봇 이동
    putRobot();          // 로봇 놓기
    return isPossible(); // 가능 여부 반환
}

int main(void)
{
    cin >> N >> K;

    conveyBelt = new Square[N * 2];
    copiedBelt = new Square[N * 2];

    for (int i = 0; i < N * 2; i++)
    {
        cin >> num;
        if (num == 0)
            numOfZero++;

        conveyBelt[i].durability = num;
    }

    // 처음부터 불가능하면 진행하지 않기
    if (numOfZero >= K)
    {
        cout << 1;
        return 0;
    }
    else
    {
        // 로봇 이동 시뮬레이션
        int timeCnt = 0;
        while (true)
        {
            timeCnt++;
            if (!cycle())
                break;
        }
        cout << timeCnt;
    }
}