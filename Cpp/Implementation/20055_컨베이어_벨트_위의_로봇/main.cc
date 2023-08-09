#include <iostream>
#include <list>
#include <deque>
using namespace std;

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

void moveBelt()
{
    // 한 칸 씩 움직이기
    for (int i = 1; i < N * 2; i++)
    {
        copiedBelt[i] = conveyBelt[i - 1];
    }
    copiedBelt[0] = conveyBelt[N * 2 - 1];

    // 올리는 위치에 도달한 녀석이라면 없애기
    if (copiedBelt[N - 1].includeRobot)
    {
        copiedBelt[N - 1].includeRobot = false;
    }

    for (int i = 0; i < N * 2; i++)
    {
        conveyBelt[i] = copiedBelt[i];
    }
}

void moveRobot()
{

    // N-1의 로봇을 N으로 옮겨 없애기
    if (conveyBelt[N - 2].includeRobot)
    {
        if (conveyBelt[N - 1].durability && !conveyBelt[N - 1].includeRobot)
        {
            conveyBelt[N - 1].durability--;
            conveyBelt[N - 2].includeRobot = false;
        }
    }

    // 1 ~ N-2의 로봇에 대해 한 칸 씩 옮길 수 있다면 옮기기
    for (int i = N - 3; i >= 0; i--)
    {
        if (conveyBelt[i].includeRobot)
        {
            if (conveyBelt[i + 1].durability && !conveyBelt[i + 1].includeRobot)
            {
                conveyBelt[i + 1].durability--;
                conveyBelt[i + 1].includeRobot = true;
                conveyBelt[i].includeRobot = false;
            }
        }
    }
}

void putRobot()
{
    if (!conveyBelt[0].includeRobot && conveyBelt[0].durability)
    {
        conveyBelt[0].includeRobot = true;
        conveyBelt[0].durability--;
    }
}

bool isPossible()
{
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
    moveBelt();
    moveRobot();
    putRobot();
    return isPossible();
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

    if (numOfZero >= K)
    {
        cout << 1;
        return 0;
    }
    else
    {
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