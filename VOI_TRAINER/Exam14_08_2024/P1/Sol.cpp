#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4;
int dp[MAXN + 5], n, m;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        for (int j = 0; c > 0; j++) {
            int val = min(c, (1 << j));
            c -= val;
            int val2 = val*u;

            for (int k = m; k >= val2; k--) {
                dp[k] = max(dp[k], dp[k - val2] + val*v);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= m; i++) ans = max(ans, dp[i]);
    
    cout << ans;
}
/*
    Goi j la bit lon nhat thoa man 2 ^ (j + 1) - 1 <= x
    Ta chung minh duoc rang co the tao ra moi so tu 0 -> x voi 2 ^ (0 -> j) va (x - (2 ^ (j + 1) - 1))
    Chung minh : 
        - Truoc het ta tao ra duoc cac so tu [0 -> 2 ^ (j + 1) - 1]
        Dat A = (x - (2 ^ (j + 1) - 1))
        --> Ta cung tao ra duoc cac so tu [0 + A, 2 ^ (j + 1) - 1 + A] = [A, x]
        Ma A <= 2 ^ (j + 1) - 1 vi neu A >= 2 ^ (j + 1) thi dang le j phai la j + 1
        --> Ta tao duoc cac so trong [0 -> 2 ^ (j + 1) - 1] giao voi [A, x] voi A <= 2 ^ (j + 1) - 1
        --> Ta tao duoc cac so tu [0 -> x]
*/