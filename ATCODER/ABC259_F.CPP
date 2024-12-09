#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;

const int MAXN = 3e5 + 5;

int n, d[MAXN];
ll dp[MAXN][2];
vector<pair<int, int>> adj[MAXN];

void dfs(int u, int p) {

    for (auto [v, w] : adj[u]) {
        if (v != p) {
            dfs(v, u);
            dp[u][0] += max(dp[v][1], dp[v][0]);
            dp[u][1] += max(dp[v][1], dp[v][0]);
        }
    }

    vector<int> vt;
    for (auto [v, w] : adj[u]) 
        if (v != p && d[v] != 0) 
            vt.emplace_back(w + dp[v][0] - max(dp[v][0], dp[v][1]));

    sort(vt.rbegin(), vt.rend());
    int temp = vt.size() - 1;

    for (int i = 0; i <= min(d[u] - 1, temp); i++) {
        if (vt[i] > 0) {
            if (i < d[u] - 1) 
                dp[u][0] += vt[i];

            dp[u][1] += vt[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> d[i];

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    dfs(1, -1);

    cout << max(dp[1][0], dp[1][1]);
}

/*
    dp[i][0] : tong trong so lon nhat khi chon nhieu nhat d[i] - 1 canh trong cay con goc u
    dp[i][1] : tong trong so lon nhat khi chon nhieu nhat d[i] canh trong cay con goc u

    luc chua chon canh nao thi dp[i][0/1] = tong max(dp[ui][0], dp[ui][1]) voi moi ui la con i
    khi chon mot canh noi i -> ui thi loi nhuan = w(i, ui) + dp[ui][0] - max(dp[ui][0], dp[ui][1]);

    => sort cac loi nhuan voi moi thang con lai => chon cac loi nhuan lon nhat > 0
*/