#include <iostream>
#include <vector>
using namespace std;

#define DIST 1000

int T, n, x, y;
vector<pair<int, int>> store;  // 편의점 리스트
pair<int, int> festival, home; // 페스티벌과 집 정보
vector<int> idx;               // 도달 가능한 편의점 인덱스 계산을 위한 리스트

bool isReachable[100];

int main(void)
{
    cin >> T;

    for (int t = 1; t <= T; t++) // 테스트 케이스 반복 횟수만큼 진행
    {
        fill_n(&isReachable[0], 100, false); // 모든 편의점 도달 불가로 초기화

        store.clear(); // 편의점 리스트 초기화

        cin >> n;                         // 맥주를 파는 편의점의 갯수
        cin >> home.first >> home.second; // 집 (시작 위치) 입력
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            store.push_back({x, y}); // 편의점 위치 추가
        }
        cin >> festival.first >> festival.second; // 페스티벌 장소 추가

        // 집에서 도달 가능한 편의점을 찾아보자
        for (int i = 0; i < n; i++)
        {
            int dist = abs(home.first - store[i].first) + abs(home.second - store[i].second);
            if (dist <= DIST)
            {
                isReachable[i] = true; // 거리 1000 이하면 도달 가능 체크
                idx.push_back(i);      // 도달 가능한 편의점 인덱스 모아놓기
            }
        }

        while (!idx.empty()) // 모아놓은 편의점 인덱스 중에서
        {
            int i = idx.at(idx.size() - 1); // 마지막 배열 원소를 빼오기 (도달 가능한 편의점 인덱스 가져오기)
            idx.pop_back();

            for (int j = 0; j < n; j++) // 모든 편의점에 대해
            {
                if (isReachable[j] == false) // 아직 도달하지 못한 편의점이라면
                {
                    int dist = abs(store[i].first - store[j].first) + abs(store[i].second - store[j].second);
                    if (dist <= DIST)
                    {                          // 길이가 1000 이하라면 도달 가능
                        isReachable[j] = true; // 도달 가능하다고 표시하기
                        idx.push_back(j);      // 탐색 대상 편의점으로 추가
                    }
                }
            }
        }
        // 도달 가능한 편의점, 집으로부터 락 페스티벌 좌표 도달 가능한지 테스트
        bool reachable = false;
        for (int i = 0; i < n; i++)
        {
            if (isReachable[i] == false) // 도달 불가하다면 페스티벌과의 거리 계산을 생략함
                continue;
            int dist = abs(store[i].first - festival.first) + abs(store[i].second - festival.second); // 페스티벌 장소와 거리 계산
            if (dist <= DIST)
            { // 1000 이하라면 페스티벌 도달 가능 플래그 표시
                reachable = true;
                break;
            }
        }

        if (!reachable)
        {                                                                                     // 편의점에서 도달 불가하다면
            int dist = abs(home.first - festival.first) + abs(home.second - festival.second); // 집에서 페스티벌 장소로 바로 갈 수 있는지 확인하기
            if (dist <= DIST)                                                                 // 거리 1000 이하라면 도달 가능
                reachable = true;
        }

        // 도달 가능하면 happy 출력, 아니라면 sad 출력
        if (reachable)
            cout << "happy\n";
        else
            cout << "sad\n";
    }
}