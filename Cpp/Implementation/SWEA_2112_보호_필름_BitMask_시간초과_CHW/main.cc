/**
 * 제한시간 초과 코드
 *
 * 왜 시간이 부족한지 모르겠다...
 * 비트 마스크로 풀고 다른 사람 코드와 특별히 다른 점이 없다고 생각하는데...
 */
#include <iostream>
using namespace std;

int T, D, W, K, answer;
int film[13], copiedFilm[13];
bool bit;

inline bool isValid()
{
    int pass = (1 << K) - 1; // 통과 최소 두께 필름
    bool valid;              // 유효성 판별
    int vertical;            // 수직 데이터 (B 기준)
    int invertedVertical;    // 수직 데이터 (A 기준)

    for (int i = 0; i < W; i++) // 모든 수직 필름에 대해
    {
        valid = false; // 테스트 통과 여부
        vertical = 0;

        int tmpI = 1 << (W - 1 - i); // 가로 인덱스 계산
        int tmpJ = 1 << D - 1;       // 세로 인덱스 계산

        for (int j = 0; j < D; j++)
        {
            if (copiedFilm[j] & tmpI) // 현재 칸에 B가 입력된 경우
                vertical |= tmpJ;     // 자릿수 작을 수록 상단 필름 레이어값 B의 경우로 체크할 때 필요한 vertical
            tmpJ >>= 1;               // 높이 1 아래로 이동
        }
        invertedVertical = ~vertical; // A의 경우로 체크할 때 필요한 inverted

        for (int j = 0; j <= D - K; j++) // bit and 연산을 통해 확인할 범위에 한해서
        {
            if ((vertical & pass) == pass) // 통과 가능 조건 확인
            {
                valid = true; // 통과
                break;        // 더 이상 확인하지 않고 다음 가로 인덱스로 넘어가자
            }

            vertical >>= 1; // 다음 칸부터 다시 탐색
        }

        if (!valid) // 보호 필름을 B로 검사했을 때 통과하지 못했다면 A로 다시 검사
        {
            for (int j = 0; j <= D - K; j++) // bit and 연산을 통해 확인할 범위에 한해서
            {
                if ((invertedVertical & pass) == pass) // 통과 가능 조건 확인
                {
                    valid = true; // 통과
                    break;        // 더 이상 확인하지 않고 다음 가로 인덱스로 넘어가자
                }

                invertedVertical >>= 1; // 다음 칸부터 다시 탐색
            }
        }

        if (!valid) // 못 찾은 경우
        {
            return false;
        }
    }

    return true; // 찾은 경우
}

inline void addLayer(int cnt, int hIdx) // hIdx 칸에 cnt 번째 약품을 투여하기
{
    if (answer <= cnt) // 더 이상 진행할 필요 없는 경우
        return;

    if (hIdx == D) // 끝까지 진행했다면
    {
        if (isValid()) // 유효성 판별
        {
            answer = cnt; // 정답 업데이트
        }

        return; // 종료
    }

    for (int idx = hIdx; idx < D; idx++)
    {
        addLayer(cnt, idx + 1); // 해당 단계 건너뛰고 진행

        copiedFilm[idx] = 0;
        addLayer(cnt + 1, idx + 1); // A를 집어넣고 다음 단계 진행

        copiedFilm[idx] = (1 << W) - 1;
        addLayer(cnt + 1, idx + 1); // B를 집어넣고 다음 단계 진행

        copiedFilm[idx] = film[idx]; // 원복
    }
}

int main(void)
{
    cin >> T;

    for (int t = 1; t <= T; t++)
    {
        cin >> D >> W >> K;
        fill_n(&film[0], 13, 0);
        fill_n(&copiedFilm[0], 13, 0);

        for (int i = 0; i < D; i++)
        {
            for (int j = W - 1; j >= 0; j--)
            {
                cin >> bit;
                if (bit)
                    film[i] |= 1 << j; // 역순으로 받아야 보기 쉬움
            }

            copiedFilm[i] = film[i];
        }

        if (isValid() || K == 1)
        {
            answer = 0;
        }
        else
        {
            answer = K;
            addLayer(0, 0);
        }

        cout << "#" << t << " " << answer << "\n";
    }
}