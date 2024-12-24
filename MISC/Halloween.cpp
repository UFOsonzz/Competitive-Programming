#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 1e9;
const long long mod = 1e9 + 7;

int n, t, max_depth[MAXN];
vector<int> adj[MAXN];
long long dp[MAXN];

long long Exp(long long a, int b) {
    if (b == 0)
        return 1;

    long long tmp = Exp(a, b / 2);
    tmp = tmp * tmp % mod;
    if (b & 1LL) 
        tmp = tmp * a % mod;
    return tmp;
}

void dfs(int u, int p, int depth) {
    max_depth[u] = depth;
    for (auto c : adj[u]) {
        if (c == p) 
            continue;
        
        dfs(c, u, depth + 1);
        max_depth[u] = max(max_depth[u], max_depth[c]);
        (dp[u] += dp[c] + Exp(2, max_depth[c] - depth - 1) - 1 + mod) %= mod;
        
    }

    (dp[u] += 1) %= mod;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("halloween.inp", "r", stdin);
    freopen("halloween.out", "w", stdout);
    
    cin >> n >> t;
    ++t;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        ++u; ++v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(t, 0, 0);

    cout << dp[t];

}