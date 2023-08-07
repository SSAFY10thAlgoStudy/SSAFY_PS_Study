#include <iostream>
#include <algorithm>
using namespace std;

int H, W;         // 가로 세로
int area[502];    // 빗물을 받는 2차원 세계를 의미
int dp[502][502]; // dp[i][j] => i~j 중 가장 높은 블록을 의미
int sum = 0;      // 빗물의 합

int main(void)
{
    cin >> H >> W;
    for (int i = 1; i <= W; i++)
    {
        cin >> area[i];
        dp[i][i] = area[i]; // dp[x][x] = 해당 가로 칸의 높이로 초기화
    }

    // 1~W에 해당하는 가로 범위에 대해 갱신하기
    for (int i = 1; i <= W; i++)
    {
        for (int j = i; j <= W; j++)
        {
            dp[i][j] = max({dp[i][j - 1], area[j]}); // dp에서 가로 한 칸을 확장할 때는 이전 높이와 현재 블록의 높이 중 최댓값을 선택한다.
        }
    }

    // dp를 구한 뒤, 합에 현재 위치 i에서 {왼쪽 최상단 높이, 오른쪽 최상단 높이} 중 작은 값과 현재 높이를 뺀 값이
    // 빗물의 높이이므로 이 값을 더한다.
    for (int i = 2; i <= W - 1; i++)
    {
        if (min(dp[1][i - 1], dp[i + 1][W]) > area[i])
            sum += min(dp[1][i - 1], dp[i + 1][W]) - area[i];
    }

    cout << sum;

    return 0;
}