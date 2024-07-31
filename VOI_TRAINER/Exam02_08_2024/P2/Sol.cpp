
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fi first
#define se second
#define print(x) cout<<"["<<(x)<<"]"
const int N = 2e3 + 5, M = 1e4 + 5;
int dp[N][M], suf[N][M], n, x, y;
pii a[N];
void cmax(int& p, int q){
    p = max(p, q);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> x >> y;
    for (int i = 1; i <= n; i++)
        cin >> a[i].fi >> a[i].se;
    sort(a + 1, a + 1 + n, [&](pii l, pii r){
        return l.se < r.se;
    });

    for (int j = 0; j <= x; j++) suf[n + 1][j] = 0;
    for (int i = n + 1; i >= 1; i--){
        for (int j = 0; j <= x; j++){
            int val = suf[i][j];
            if (a[i - 1].fi + j <= x)
                cmax(suf[i - 1][j + a[i - 1].fi], val + 1);
            cmax(suf[i - 1][j], val);
        }
    }
    int ans = 0;
    memset(dp, -1, sizeof dp);
    dp[0][x] = y;
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= x; j++){
            if (dp[i][j] < 0) continue;
            int val = dp[i][j];
            cmax(ans, i + suf[i + 1][j]);
            if (i == n) continue;
            if (a[i + 1].fi <= j)
                cmax(dp[i + 1][j - a[i + 1].fi], val);
            if (a[i + 1].se <= val)
                cmax(dp[i + 1][j], val - a[i + 1].se);
        }
    }
    cout << ans;
}
