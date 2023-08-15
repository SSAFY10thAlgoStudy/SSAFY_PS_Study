#include <iostream>
#include <queue>
using namespace std;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int diff = 400;

int area[800][800];

typedef struct Cell
{
    int y, x;
    int health;
    int remain;

    Cell(int y, int x, int health, int remain)
    {
        this->y = y;
        this->x = x;
        this->health = health;
        this->remain = remain;
    }
} Cell;

struct compare
{
    bool operator()(Cell a, Cell b)
    {
        if (b.remain == 0 && a.remain != 0)
            return true;

        if (a.health > b.health)
        {
            return true;
        }

        return false;
    }
};
priority_queue<Cell, vector<Cell>, compare> deactive, active, dead, tmp_q;

int K, curTime = 0, N, M, T, health;

void update()
{
    while (!active.empty())
    {
        auto elem = active.top();
        if (elem.remain == 0)
        {
            // 활성 상태의 세포 중 생명력이 0인 녀석들을 제거
        }
        else
        {
            // 활성 상태의 세포 중 생명력이 남아있다면 번식시키기
            for (int d = 0; d < 4; d++)
            {
                int ny = elem.y + dy[d];
                int nx = elem.x + dx[d];

                // 죽어 있는 세포의 공간이 아니고 비활성 상태의 세포가 있는 공간이 아니라면
                if (area[ny][nx] >= 0)
                {
                    area[ny][nx] = elem.health;
                    deactive.push(Cell(ny, nx, health, health));
                }
            }
        }
    }

    // deactive 중 활성화 시간에 다다른 녀석들은 꺼내서 활성화 세포 큐에 집어넣는다
    while (!deactive.empty())
    {
        if (deactive.top().remain == 0)
        {
            auto elem = deactive.top();
            deactive.pop();
            elem.remain = health;
            active.push(elem);
        }
    }
    tmp = deactive;
    while (!)
}
int main(void)
{
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> M >> K;

        // 초기 설정
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                cin >> area[i][j];
                if (area[i][j] > 0)
                {
                    // 줄기 세포의 경우
                    deactive.push(Cell(i, j, health, health));
                }
            }
        }

        for (int spent = 0; spent < K; spent++)
        {
            update();
        }
    }
    return 0;
}