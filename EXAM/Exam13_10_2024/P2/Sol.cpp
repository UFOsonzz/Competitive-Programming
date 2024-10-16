#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;

int n, k;
int a[MAXN];
int p[MAXN], dp[MAXN], suff[MAXN];
bool ans[MAXN];
int maxs;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        p[i] = i;
    }

    sort(p + 1, p + n + 1, [&](int x, int y) {
        return a[x] > a[y];
    });

    for (int i = n; i >= 1; --i) {
        if (a[p[i]] >= k) {
            suff[i] = suff[i + 1];
        } else {
            suff[i] = suff[i + 1] + a[p[i]];
        }
    }

    dp[0] = 1;
    maxs = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[p[i]] >= k) {
            ans[p[i]] = 1;
        } else {
            if (maxs + suff[i + 1] >= k - a[p[i]]) {
                ans[p[i]] = 1;
            }
            for (int j = k; j >= 0; --j) {
                if (dp[j]) {
                    if (j + a[p[i]] < k) {
                        maxs = max(maxs, j + a[p[i]]);
                        dp[j + a[p[i]]] = 1;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i];
    }

    return 0;
}
