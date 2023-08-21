#include <iostream>
using namespace std;

int n, m, a, b, cmd; // n: vertex 갯수, m: 간선 갯수, a: 입력 정점1, b: 입력 정점2, cmd: 연산 구분
int parent[1000001]; // parent[x]: x 정점이 속한 최상위 부모 (x,y 합집합 시 작은 수의 인덱스를 사용한다)

/**
 * 최상위 부모를 찾기 위한 함수
 * 주어진 x에 대해 parent 배열에서 찾아놓은 부모를 재귀적으로 찾아가며 검사함
 *
 * 최악의 시간복잡도 : O(N) 한쪽으로만 치우쳐져 있는 트리. 링크드 리스트 탐색과 같음
 * 평균 시간복잡도 : O(NlogN) 균형 잡혀 있는 트리의 경우 트리의 높이만큼 탐색
 */
int find_parent(int x)
{
    if (parent[x] == x) // 이미 최상위 노드가 자기 자신으로 설정된 경우
    {
        return x; // 자기 자신이 루트기 때문에 바로 반환
    }
    else // 부모 노드가 자기 자신이 아닌 경우
    {
        return parent[x] = find_parent(parent[x]); // 상위의 부모 노드가 있나 확인하여 업데이트
    }
}

void union_parent(int x, int y)
{
    x = find_parent(x); // x의 최상위 부모 찾기
    y = find_parent(y); // y의 최상위 부모 찾기

    if (x == y) // 찾은 부모가 동일하면
    {
        return; // 이미 합집합이므로 종료
    }
    else // 최상위 부모가 다르다면
    {
        if (x < y) // y가 큰 경우
        {
            parent[y] = x; // y보다 작은 x를 기준으로 합친다 (x가 상단 노드임을 의미)
        }
        else
        {
            parent[x] = y; // x보다 작은 y를 기준으로 합친다 (y가 상단 노드임을 의미)
        }
    }
}

int main(void)
{
    // 이 문제는 입력의 갯수가 많기 때문에 빠른 입출력을 요한다.
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;               // 정점의 갯수와 연산의 갯수를 입력받는다.
    for (int i = 1; i <= n; i++) // 모든 정점에 대해 아직 다른 집합과 합집합을 하지 않았으므로 부모는 자기 자신이다.
    {
        parent[i] = i;
    }
    for (int i = 0; i < m; i++) // 주어진 연산 갯수만큼 반복하기
    {
        cin >> cmd >> a >> b; // 연산 종류, 정점 입력 받기
        if (cmd == 0)
        {
            if (a != b)             // a와 b가 동일하다면 연산을 할 필요가 없다.
                union_parent(a, b); // a,b 합집합 수행 (트리에서 최상위 부모 노드를 동일하게 하는 효과)
            // a < b라면, b의 부모는 a가 된다.
        }
        else
        {
            if (a == b || find_parent(a) == find_parent(b)) // a,b가 동일하면 같은 집합, a,b 각각의 최상위 부모가 동일하면 같은 집합
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
}