#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
const int K = 5e3 + 5;
const int INF = 1E9 + 1;
int n, k, dp[N][K], val[N][N];
using T3 = tuple<int, int, int>;
void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            cin >> val[i][j];
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = -INF;
        }
    }
    dp[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        priority_queue<T3> pq;
        for (int j = 1; j <= i; j++) {
            pq.emplace(val[j][i] + (j < 2 ? 0 : dp[j - 2][1]), (j < 2 ? -1 : (j - 2)), 1);
        }
        int cnt = 0;
        while (cnt < k && !pq.empty()) {
            ++cnt;
            int u, v, c;
            tie(u, v, c) = pq.top();
            dp[i][cnt] = u;
            pq.pop();
            if (c < k && v != -1) pq.emplace(val[v + 2][i] + dp[v][c + 1], v, c + 1);
        }
        vector<int> tmp;
        int j = 1;
        for (int t = 1; t <= k && tmp.size() < k; t++) {
            while (j <= k && dp[i - 1][j] >= dp[i][t] && tmp.size() < k) {
                tmp.push_back(dp[i - 1][j++]);
            }
            if (tmp.size() < k) tmp.push_back(dp[i][t]);
        }
        for (int t = 0; t < tmp.size(); t++) {
            dp[i][t + 1] = tmp[t];
        }
    }
    for (int i = 1; i <= k; i++) cout << dp[n][i] << " ";
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();

}
/*
1
1 2
-5

*/