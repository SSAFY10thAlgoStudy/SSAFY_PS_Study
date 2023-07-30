#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#define MAX 10001
int n;

bool visited[MAX];
vector<pair<int, int>> tree[MAX];

int main(void)
{
    cin >> n;
    if (n == 1)
    {
        cout << 0;
        return 0;
    }

    int u, v, w;
    for (int i = 1; i < n; i++)
    {
        cin >> u >> v >> w;
        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
    }

    fill_n(&(visited[0]), MAX, false);

    int maxCost = -1, maxIdx = -1;

    stack<pair<int, int>> st;
    st.push({1, 0});
    visited[1] = true;

    while (!st.empty())
    {
        auto elem = st.top();
        st.pop();

        int curIdx = elem.first;
        int curCost = elem.second;

        if (curCost > maxCost)
        {
            maxCost = curCost;
            maxIdx = curIdx;
        }

        for (auto nextElem : tree[curIdx])
        {
            int nextIdx = nextElem.first;
            int nextCost = curCost + nextElem.second;

            if (!visited[nextIdx])
            {
                visited[nextIdx] = true;
                st.push({nextIdx, nextCost});
            }
        }
    }

    st.push({maxIdx, 0});
    fill_n(&(visited[0]), MAX, false);
    maxCost = 0;
    visited[maxIdx] = true;

    while (!st.empty())
    {
        auto elem = st.top();
        st.pop();

        int curIdx = elem.first;
        int curCost = elem.second;

        if (curCost > maxCost)
        {
            maxCost = curCost;
            maxIdx = curIdx;
        }

        for (auto nextElem : tree[curIdx])
        {
            int nextIdx = nextElem.first;
            int nextCost = curCost + nextElem.second;

            if (!visited[nextIdx])
            {
                visited[nextIdx] = true;
                st.push({nextIdx, nextCost});
            }
        }
    }

    cout << maxCost;
    return 0;
}