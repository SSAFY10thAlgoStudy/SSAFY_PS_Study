#include <iostream>
#include <stack>
#include <vector>
using namespace std;

char sudoku[10][10];	// '1'~'9'가 들어가는 sudoku 보드를 의미한다. 인덱스 계산의 용이성을 위해 (1,1)부터 시작하도록 설정
int vertical[10];		// 스도쿠 수직 합을 저장하는 변수 (vertical[3] => 3번 열의 합)
int horizontal[10];		// 스도쿠 수평 합을 저장하는 변수 (horizontal[7] => 7번 행의 합)
int inBound[10];		// 3x3 정사각형을 떼 좌측 상부를 인덱스 1로, 우측 하부를 인덱스 9로 설정한 변수
vector<pair<int, pair<int, int>>> emptyCoord;	// '0'으로 표기된 좌표 위치를 저장하는 리스트
bool isFinished = false;	// 조합 생성 완료 플래그 => 맨 처음 해답을 구하고 플래그가 설정되면 그 이후에 수행되는 재귀를 더 이상 실행하지 않는다

/*
좌표 (y,x)를 받아 3x3 정사각형 스도쿠 인덱스 반환
*/
int calcInBound(int y, int x)
{
    return ((y - 1) / 3) * 3 + ((x - 1) / 3) + 1;
}

/*
현재 추가하려는 위치 (y,x)에 val을 대입 후 스도쿠 규칙을 만족하나 체크하는 함수
*/
bool isDuplicated(int y, int x, int val)
{
    int bitVal = (1 << (val - 1));	// 비트 값 변환

	// 변환한 비트값과 가로 세로 3x3 3가지 경우와 겹치는 경우가 있다면 true 반환
    if ((bitVal & horizontal[y]) | (bitVal & vertical[x]) | (bitVal & inBound[calcInBound(y, x)]))
        return true;
    return false;
}

/*
스도쿠 출력
*/
void printSudoku()
{
    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            cout << sudoku[i][j];
        }
        cout << "\n";
    }
}

/*
remaining : 추가적으로 값을 대입해줘야 하는 남은 emptyCoord 갯수

남은 emptyCoord 대상으로 하나씩 새로운 값을 채워나가 재귀 백트래킹을 수행한다.
*/
void findCombination(int remaining)
{
    if (isFinished)	// 이미 해답을 찾은 경우 함수 종료
        return;

    if (remaining == 0)	// 모든 emptyCoord를 채운 경우
    {
        isFinished = true;	// 해답을 찾은 경우
        printSudoku();

        return;
    }
    else
    {
		// 현재 좌표 값 받아오기
        pair<int, pair<int, int>> curCoord = emptyCoord[emptyCoord.size() - remaining];
        int y = curCoord.second.first;
        int x = curCoord.second.second;
        // int val = curCoord.first;

        int ret = horizontal[y] | vertical[x] | inBound[calcInBound(y, x)];
		// 1~9 조합을 통해
        for (int val = 1; val < 10; val++)
        {
			// 스도쿠 조건을 만족하지 않으면 생략
            if (isDuplicated(y, x, val))
            {
                continue;
            }
            else
            {
                sudoku[y][x] = (char)('0' + val);							// 스도쿠에 값 넣기
                horizontal[y] |= 1 << (val - 1);							// horizontal 갱신
                vertical[x] |= 1 << (val - 1);								// vertical 갱신
                inBound[calcInBound(y, x)] |= 1 << (val - 1);				// 3x3 갱신
                emptyCoord[emptyCoord.size() - remaining].first = val;		// 현재 진행 상황 저장

                findCombination(remaining - 1);								// 다음 단계 진행

                sudoku[y][x] = '0';											// 스도쿠 원복
                horizontal[y] -= 1 << (val - 1);							// horizontal 원복
                vertical[x] -= 1 << (val - 1);								// vertical 원복
                inBound[calcInBound(y, x)] -= 1 << (val - 1);				// 3x3 원복
                emptyCoord[emptyCoord.size() - remaining].first = 0;		// emptyCoord 값을 본래 값인 0으로 설정
            }
        }
    }
}

int main(void)
{
	// 초기화
    fill_n(&vertical[0], 10, 0);
    fill_n(&horizontal[0], 10, 0);
    fill_n(&inBound[0], 10, 0);

    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            cin >> sudoku[i][j];	// 스도쿠 입력 받기
            if (sudoku[i][j] != '0')	// 숫자가 입력된 경우 horizontal, vertical, 3x3의 해당 인덱스로 접근해 스도쿠에 들어온 값을 갱신해주기
            {
                horizontal[i] |= (1 << ((int)(sudoku[i][j] - '0') - 1));
                vertical[j] |= (1 << ((int)(sudoku[i][j] - '0') - 1));
                inBound[calcInBound(i, j)] |= (1 << ((int)(sudoku[i][j] - '0') - 1));
            }
            else
            {
                emptyCoord.push_back({0, {i, j}});	// 빈 좌표 추가
            }
        }
    }

    findCombination(emptyCoord.size());

    return 0;
}