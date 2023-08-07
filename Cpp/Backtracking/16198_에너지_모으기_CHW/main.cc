#include <iostream>
using namespace std;

int N;
bool used[10];
int W[10];
int answer = -1, cnt = 0;

/**
 * idx로부터 사용하지 않은 좌 (lt = true), 우 (lt = false) 데이터를 반환한다.
 * 없다면 -1 반환
 */
int findIndex(int idx, bool lt)
{
    if (lt)
    {
        for (int i = idx - 1; i >= 0; i--)
        {
            if (!used[i])
                return i;
        }
    }
    else
    {
        for (int i = idx + 1; i < N; i++)
        {
            if (!used[i])
                return i;
        }
    }

    return -1;
}

/**
 * 현재까지 수집한 에너지 val에 대해 남아있는 W 원소가 2개가 될 때까지
 * 모든 부분 집합을 탐색하는 백트래킹을 진행한다.
 */
void collect(int val)
{
    if (cnt == 2) // W에서 사용하지 않은 원소의 수가 2인 경우, 더 이상 진행 불가
    {
        if (val > answer)
        {
            answer = val;
        }
    }
    else
    {
        int ltIdx, gtIdx;
        for (int i = 1; i < N - 1; i++)
        {
            if (!used[i])
            {
                ltIdx = findIndex(i, true);  // i번째 원소를 꺼낼 시 사용하게 될 좌측 인덱스
                gtIdx = findIndex(i, false); // i번째 원소를 꺼낼 시 사용하게 될 우측 인덱스

                if (ltIdx < 0 || gtIdx < 0) // 남아 있는 좌우측 원소가 하나라도 없다면 생략
                    continue;

                // 변수 설정
                used[i] = true;
                cnt--;
                collect(val + W[ltIdx] * W[gtIdx]); // 추가 진행
                // 원상 복구
                cnt++;
                used[i] = false;
            }
        }
    }
}

int main(void)
{
    cin >> N;
    int tmp;
    fill_n(&used[0], N, false);
    for (int i = 0; i < N; i++)
    {
        cin >> W[i];
    }
    cnt = N;
    collect(0);

    cout << answer;
}