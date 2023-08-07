#include <iostream>
#include <cmath>
#include <string>
using namespace std;

#define DIGIT_LIMIT 5
string str;
int copiedNumber, currentNumber = 1, digitSize = 1, digits[DIGIT_LIMIT], digitIdx;

int main(void)
{

    cin >> str;

    int strIdx = 0, strLen = str.size(), divid;
    while (strIdx < strLen)
    {
        copiedNumber = currentNumber;
        char ch = str.at(strIdx);

        divid = pow(10, DIGIT_LIMIT - 1);
        digitSize = -1;

        // 각 자릿수 설정 ex) 19234 => [1,9,2,3,4],  326 => [0,0,3,2,6] 과 같이 저장
        for (int i = 0; i < DIGIT_LIMIT; i++)
        {
            digits[i] = copiedNumber / (divid); // 10^(DIGIT_LIMIT-1)의 자리 ~ 1의 자리까지 구하기
            if (digitSize < 0 && digits[i] > 0) // 가장 먼저 0보다 큰 수가 나온 자릿수가 그 수의 자릿수
                digitSize = DIGIT_LIMIT - i;

            copiedNumber -= digits[i] * divid; // 다음 자릿수를 구하기 위한 설정
            divid /= 10;
        }

        // 구한 숫자와 일치하는 문자 개수만큼 건너뛰기
        for (int i = DIGIT_LIMIT - digitSize; i < DIGIT_LIMIT; i++)
        {
            if (ch == digits[i] + '0')
            {
                strIdx++;
                if (strIdx == strLen)
                    break;
                ch = str.at(strIdx);
            }
        }

        currentNumber++;
    }

    cout << currentNumber - 1;
}