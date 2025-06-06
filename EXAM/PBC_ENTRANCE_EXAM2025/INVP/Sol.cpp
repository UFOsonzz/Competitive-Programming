#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int K = 105;
const long long INF = 1e18;

int a[N], w[K];
pair<long long, long long> dp[N][K];

void update(pair<long long, long long> que, long long Add, pair<long long, long long>& val) {
    if (que.first + Add > val.first) {
        val = {que.first + Add, que.second};
    } else if (que.first + Add == val.first) {
        val.second += que.second;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= k; i++)
        cin >> w[i];
    
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= k; j++)
            dp[i][j] = {-INF, 0};

    dp[0][0] = {0, 1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            if (dp[i][j].first == -INF)
                continue;
            if (j < k) {
                update(dp[i][j], 1LL * a[i + 1] * w[j + 1], dp[i + 1][j + 1]);
            }

            update(dp[i][j], 0, dp[i + 1][j]);
        }
    }

    cout << dp[n][k].first << '\n' << dp[n][k].second;
}