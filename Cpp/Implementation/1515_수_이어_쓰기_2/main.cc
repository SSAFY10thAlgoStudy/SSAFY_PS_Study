#include <iostream>
#include <string.h>
#include <string>
using namespace std;

string str;
int main(void)
{
    cin >> str; // 문자열 입력 받기

    int cnt = 1;
    int index = 0;
    bool isContain = false;

    // 현재까지 카운팅한 숫자와 지금 맞딱뜨린 문자와 일치하는 부분이 존재할 때
    // 카운팅 숫자 문자열과 맞딱뜨린 문자열과 일치하는 부분만큼 건너뛰고
    // 숫자 증가

    while (index < str.size()) // 문제에서 주어진 문자열을 모두 검사할 때 까지
    {
        isContain = false;                      // 현재 숫자를 문자열로 바꿨을 때 현재 인덱스의 문자를 포함하는지 확인하는 플래그
        string number = to_string(cnt);         // 숫자를 문자열로 변환
        for (int i = 0; i < number.size(); i++) // 현재 숫자에 대해
        {
            if (number.at(i) == str.at(index)) // 지금 확인하는 문자와 겹친다면
            {
                isContain = true; // 포함 관계 성립
                break;
            }
        }

        if (isContain) // 겹치는 문자가 하나라도 있다면
        {
            for (int i = 0; i < number.size(); i++) // 현재 카운팅하는 숫자를
            {
                if (index < str.size() && number.at(i) == str.at(index)) // 문자열과 비교해 매칭되면 문자열 탐색 인덱스 증가
                {
                    index++;
                }
            }
        }
        cnt++; // 다음 숫자로 넘어가 확인을 계속한다.
    }

    cout << cnt - 1; // 마지막에 cnt++한 동작은 필요없으므로 -1로 마무리

    return 0;
}