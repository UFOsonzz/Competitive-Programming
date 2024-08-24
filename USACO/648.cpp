#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1 << 18;
const int MAXV = 60;

int n, a[MAXN + 5], dp[MAXV + 2][MAXN + 5];

int main() {
    freopen("262144.in", "r", stdin);
    freopen("262144.out", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    int ans = 0;

    for (int t = 1; t <= MAXV; t++) {
        for (int i = 1; i <= n; i++) {
            if (a[i] == t) dp[t][i] = i + 1;
            else dp[t][i] = dp[t - 1][dp[t - 1][i]];

            if (dp[t][i] != 0) ans = max(ans, t);
        }
    }

    cout << ans;
}