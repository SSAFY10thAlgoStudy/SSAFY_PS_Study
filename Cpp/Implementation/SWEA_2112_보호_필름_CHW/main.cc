#include <stdio.h>
#define A 0
#define B 1
#define min(a, b) ((a) > (b) ? (b) : (a))
int inject[13];

bool isPass(bool map[13][20], int d, int w, int k)
{
    for (int j = 0; j < w; j++)
    {
        int cnt = 1;
        int s = inject[0] != -1 ? inject[0] : map[0][j];
        for (int i = 1; i < d; i++)
        {
            int nowS = inject[i] != -1 ? inject[i] : map[i][j];
            if (s == nowS)
            {
                cnt++;

                if (cnt == k)
                {
                    break;
                }
            }
            else
            {
                cnt = 1;
                s = nowS;
            }
        }

        if (cnt < k)
        {
            return false;
        }
    }

    return true;
}

bool globalMap[13][20];
bool isPossible(int row, int d, int w, int k, int dep, int depMax, int taget)
{
    if (dep == depMax)
    {
        return isPass(globalMap, d, w, k);
    }
    else if (row >= d)
    {
        return false;
    }

    if (isPossible(row + 1, d, w, k, dep, depMax, taget))
    {
        return true;
    }

    inject[row] = taget;
    bool result = isPossible(row + 1, d, w, k, dep + 1, depMax, taget);
    inject[row] = -1;

    return result;
}

int solve(int d, int w, int k, int l, int r, int target)
{
    int ans = d - 1;
    if (target == B)
    {
        if (isPossible(0, d, w, k, 0, r, target))
        {
            ans = r;
            r = (l + r) / 2 - 1;
        }
        else
        {
            return ans;
        }
    }

    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (isPossible(0, d, w, k, 0, mid, target))
        {
            if (ans > mid)
            {
                ans = mid;
            }
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    return ans;
}

int main()
{
    int t;
    scanf("%d", &t);

    for (int tc = 1; tc <= t; tc++)
    {
        int d, w, k;
        scanf("%d %d %d", &d, &w, &k);

        for (int i = 0; i < d; i++)
        {
            inject[i] = -1;
            for (int j = 0; j < w; j++)
            {
                scanf("%d", &globalMap[i][j]);
            }
        }

        int ansA = solve(d, w, k, 0, d - 1, A);
        int ans = min(ansA, solve(d, w, k, 0, ansA - 1, B));

        printf("#%d %d\n", tc, ans);
    }
    return 0;
}