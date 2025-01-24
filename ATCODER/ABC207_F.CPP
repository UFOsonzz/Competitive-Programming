#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2005;
const ll mod = 1e9 + 7;

int n, sz[MAXN];
vector<int> adj[MAXN];
ll dp[MAXN][MAXN][3], tmp[MAXN][3];

void add(ll &x, ll y) {
    x += y;
    if (x >= mod) x -= mod;
}

void dfs(int p, int u) {
    dp[u][0][0] = dp[u][1][1] = sz[u] = 1;

    for (auto c: adj[u]) {
        if (c == p) continue;
        dfs(u, c);

        memset(tmp, 0, sizeof tmp);

        for (int i = sz[u]; i >= 0; i--) {
            for (int j = sz[c]; j >= 0; j--) {
                add(tmp[i + j][0], dp[u][i][0] * (dp[c][j][0] + dp[c][j][2]) % mod);
                add(tmp[i + j][1], dp[u][i][1] * ((j ? dp[c][j - 1][0] : 0) + dp[c][j][1] + dp[c][j][2]) % mod);
                add(tmp[i + j][2], (dp[u][i][2] * (dp[c][j][2] + dp[c][j][0] + dp[c][j][1]) + (i ? dp[u][i - 1][0] : 0) * dp[c][j][1]) % mod);
            }
        }

        sz[u] += sz[c];
        for (int i = 0; i <= sz[u]; i++)
            for (int j = 0; j < 3; j++)
                dp[u][i][j] = tmp[i][j];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, 1);

    for (int i = 0; i <= n; i++) 
        cout << (dp[1][i][0] + dp[1][i][1] + dp[1][i][2]) % mod << '\n';
}

/*
    // BAI DE KNAPSACK ON TREE NEN GIANG CU THE
    dp[i][j][0/1/2] = x;
    đến subtree i, có j thằng được bảo vệ, (3 trạng thái), và x cách để đạt được trạng thái này

    trạng thái 0 : 0 đặt takahashi ở i, đỉnh i chưa được bảo vệ
    trạng thái 1 : 0 đặt takahashi ở i, nhưng đỉnh i được bảo vệ
    trạng thái 2 : đặt takahashi tại i, đỉnh i được bảo vệ

    dp[i][j]
    dp[i2][0,1,2,...sz[i2]]
    dp[i2][j2]


    thăm từng thằng con của i
    giả sử thăm đến con ij, có size subtree là sz[ij]

    for (j : số thằng đã thăm hiện tại trong subtree của i) {
        for (j2 : số thằng có trong shop ij (0 -> sz[ij])) {
            // vi du voi 4 truong hop

            (i/0 ij/0) : dp[i][j + j2][0] += dp[i][j][0] * dp[ij][j2][0];
            (i/0 ij/1) : dp[i][j + j2][0] += dp[i][j][0] * dp[ij][j2][1];
            (i/0 ij/2) : dp[i][j + j2 + 1][1] += dp[i][j][0] * dp[ij][j2][2];
            (i/1 ij/1) : dp[i][j + j2][1] += dp[i][j][1] * dp[ij][j2][1];
        }
    }

    sz[i] += sz[ij];    

*/