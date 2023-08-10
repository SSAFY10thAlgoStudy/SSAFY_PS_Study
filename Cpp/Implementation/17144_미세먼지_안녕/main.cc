#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define MAX 51
int R, C, T;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

// 공기 청정기 1의 이동 순서
int cy1[] = {-1, 0, 1, 0};
int cx1[] = {0, 1, 0, -1};

// 공기 청정기 2의 이동 순서
int cy2[] = {1, 0, -1, 0};
int cx2[] = {0, 1, 0, -1};

int map[MAX][MAX];
int copiedMap[MAX][MAX]; // 이동 결과를 쉽게 업데이트하기 위한 복사 배열

typedef struct Dirt // 미세먼지는 좌표값과 미세먼지 농도로 구성
{
    int y, x;
    int amount = 0;

    Dirt(int y, int x)
    {
        this->y = y;
        this->x = x;
    }

    Dirt(int y, int x, int amount)
    {
        this->y = y;
        this->x = x;
        this->amount = amount;
    }
} Dirt;

vector<pair<int, int>> cleaner; // 공기청정기

void printMap();
bool isIn(int y, int x);
int sumOfDirt();
int simulation();
void update();
void spreadDirt();
void cleaning();

void printMap()
{
    cout << "\n\n";
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

// 좌표 값이 맵 내부인지 판별하기
bool isIn(int y, int x)
{
    return (1 <= y && y <= R) && (1 <= x && x <= C);
}

/*
미세먼지 합을 반환
*/
int sumOfDirt()
{
    int sum = 0;
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            if (map[i][j] > 0)
                sum += map[i][j];
        }
    }
    return sum;
}

/*
미세먼지 확산 및 공기청정기 시뮬레이션 후 미세먼지 총합 반환
*/
int simulation()
{
    update();
    return sumOfDirt();
}

/*
주어진 시간만큼 프로세스 업데이트
*/
void update()
{
    while (T--)
    {
        spreadDirt();
        cleaning();
    }
}

/*
미세먼지 확산 프로세스
*/
void spreadDirt()
{
    fill_n(&copiedMap[0][0], MAX * MAX, 0); // 결과값 저장 배열 초기화
    int ny, nx, val, cnt;

    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            if (map[i][j] > 0) // 미세먼지 존재 시 수식에 따라 업데이트하기
            {
                cnt = 0;                // 상하좌우 미세먼지 중 확산 가능 갯수
                val = map[i][j];        // 현재 미세먼지 값
                copiedMap[i][j] += val; // 결과값 저장 배열에 현재값 저장

                for (int d = 0; d < 4; d++) // 상하좌우에 대해
                {
                    // 이동 후 좌표 계산
                    ny = i + dy[d];
                    nx = j + dx[d];

                    // 맵 내부이며, 공기청정기의 위치가 아닐 때
                    if (isIn(ny, nx) && map[ny][nx] >= 0)
                    {
                        // 확산시켜 1/5 값을 적고, 확산된 미세먼지 갯수 카운트 증가
                        copiedMap[ny][nx] += val / 5;
                        cnt++;
                    }
                }

                if (cnt) // 확산 시 확산 칸 수 만큼 원본 미세먼지 감소시키기
                {
                    copiedMap[i][j] -= val / 5 * cnt;
                }
            }
        }
    }

    // 원본 배열로 이동시키기
    memcpy(map, copiedMap, sizeof(copiedMap));
}

/*
공기청정 프로세스
*/
void cleaning()
{
    // 공기청정기 위치
    int sy1 = cleaner[0].first;
    int sx1 = cleaner[0].second;
    int sy2 = cleaner[1].first;
    int sx2 = cleaner[1].second;

    // 공기 이동 위치 시작점 초기화
    int y1 = sy1, x1 = sx1, y2 = sy2, x2 = sx2;

    // 공기 순환 후 -1로 다시 원복시킬 예정 (swap을 위해 잠시 0으로 설정)
    map[sy1][sx1] = 0;
    map[sy2][sx2] = 0;
    int tmp;

    // 4방향 순환을 하며
    for (int d = 0; d < 4; d++)
    // 맵 내부로 이동 가능한 상황을 넘어서면 자동으로 while문을 빠져나와 방향을 전환시킨다.
    {
        // 맵 내부에서 이동 시 방향을 유지하며 swap을 통해 순환을 구현 (윗 방향 청정기)
        while (1 <= y1 + cy1[d] && y1 + cy1[d] <= sy1 && 1 <= x1 + cx1[d] && x1 + cx1[d] <= C)
        {
            tmp = map[y1][x1];
            map[y1][x1] = map[y1 + cy1[d]][x1 + cx1[d]];
            map[y1 + cy1[d]][x1 + cx1[d]] = tmp;
            y1 = y1 + cy1[d];
            x1 = x1 + cx1[d];
        }

        // 맵 내부에서 이동 시 방향을 유지하며 swap을 통해 순환을 구현 (아랫 방향 청정기)
        while (sy2 <= y2 + cy2[d] && y2 + cy2[d] <= R && 1 <= x2 + cx2[d] && x2 + cx2[d] <= C)
        {

            tmp = map[y2][x2];
            map[y2][x2] = map[y2 + cy2[d]][x2 + cx2[d]];
            map[y2 + cy2[d]][x2 + cx2[d]] = tmp;
            y2 = y2 + cy2[d];
            x2 = x2 + cx2[d];
        }
    }

    // 공기청정기로 원복 (-1), 공기청정되어 나온 미세먼지 (0)으로 초기화
    map[sy1][sx1] = -1;
    map[sy1][sx1 + 1] = 0;
    map[sy2][sx2] = -1;
    map[sy2][sx2 + 1] = 0;
}

int main()
{

    cin >> R >> C >> T;

    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            cin >> map[i][j];
            if (map[i][j] < 0)
            {
                cleaner.push_back({i, j});
            }
        }
    }

    cout << simulation();
    return 0;
}
