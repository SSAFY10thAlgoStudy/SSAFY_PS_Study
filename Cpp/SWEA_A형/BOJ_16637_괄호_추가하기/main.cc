#include <iostream>
using namespace std;

string s;
int N, answer = -2e9;

void dfs(int idx, int res);
int calc(int a, int b, char oper);

int main(void)
{
    cin >> N;
    cin >> s;

    dfs(0, 0);

    cout << answer;
    return 0;
}

void dfs(int idx, int res)
{
    if (idx >= N) // 종료 조건
    {
        answer = max(answer, res);
        return;
    }

    char oper = (idx == 0) ? '+' : s[idx - 1]; // 계산하고 앞에 남아있는 연산자

    if (idx + 2 < N)
    {
        // 괄호로 묶으면 먼저 계산하기
        int brace = calc(s[idx] - '0', s[idx + 2] - '0', s[idx + 1]);
        dfs(idx + 4, calc(res, brace, oper));
    }

    // 괄호로 안 묶고 다음 연산자 계산하기
    dfs(idx + 2, calc(res, s[idx] - '0', oper));
}

int calc(int a, int b, char oper)
{
    switch (oper)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    }

    return a;
}