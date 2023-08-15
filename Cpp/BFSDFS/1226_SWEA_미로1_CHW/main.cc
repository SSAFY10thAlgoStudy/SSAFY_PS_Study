#include <iostream>
#include <stack>
using namespace std;

char map[16][16];
pair<int, int> start, finish;
stack<pair<int, int>> st;
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
bool visited[16][16];

int main(void)
{
    for (int t = 1; t <= 10; t++)
    {
        cin >> t;
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                cin >> map[i][j];
                if (map[i][j] == '2')
                {
                    start = {i, j};
                }
                else if (map[i][j] == '3')
                {
                    finish = {i, j};
                }
            }
        }

        fill_n(&visited[0][0], 16 * 16, false);

        st.push(start);
        while (!st.empty())
        {
            pair<int, int> popped = st.top();
            st.pop();
            visited[popped.first][popped.second] = true;

            for (int d = 0; d < 4; d++)
            {
                int ny = popped.first + dy[d];
                int nx = popped.second + dx[d];
                if (!visited[ny][nx] && map[ny][nx] != '1')
                {
                    if (map[ny][nx] == '0' || map[ny][nx] == '3')
                    {
                        st.push({ny, nx});
                    }
                }
            }
        }

        if (visited[finish.first][finish.second])
            cout << "#" << t << " 1\n";
        else
            cout << "#" << t << " 0\n";
    }
    return 0;
}