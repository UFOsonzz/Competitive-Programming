#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e5 + 5;

int n, a[MAXN], sz[MAXN];
vector<pair<int, int>> adj[MAXN];
ll ans[MAXN];

void dfs1(int p, int u) {
    sz[u] = 1;

    for (auto c : adj[u]) {
        if (c.first == p)
            continue;

        dfs1(u, c.first);
        sz[u] += sz[c.first];
        ans[1] += 1LL * c.second * sz[c.first];
    }
}

void dfs2(int p, int u) {
    for (auto c : adj[u]) {
        if (c.first == p)
            continue;
        ll lost = 1LL * c.second * sz[c.first];
        ll add = 1LL * c.second * (n - sz[c.first]);
        ans[c.first] = ans[u] - lost + add;

        dfs2(u, c.first);
    }
}

void solve() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        adj[i].clear();
        ans[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v, a[u] ^ a[v]);
        adj[v].emplace_back(u, a[u] ^ a[v]);
    }

    dfs1(0, 1);
    dfs2(0, 1);

    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;

    while (t--)
        solve();

}

/*
    de tat ca cac node co gia tri bang nhau thi xor cua 2 thang o moi canh phai bang 0
    dinh nghia trong so canh bang a[u] ^ a[v] => bien tat ca cac canh thanh 0
    xet canh u <-> pa[u], cach duy nhat de lam thay doi trong so cua canh nay la thuc hien mot thao tac o subtree u
    => thuc hien thao tac xor toan bo thang voi val = a[u] ^ a[pa[u]] => cost = val * sz[u]
    neu tach val = val1 ^ val2 ^ val3..., va thuc hien cac thao tac tren subtree u voi val1, val2, val3...
    thi cost =  (val1 + val2 + val3 + ...) * sz[u] >= (val1 ^ val2 ^ val3 ^ ...) * sz[u] = val * sz[u] => chi update 1 lan
    => bai toan tro thanh tinh tong (a[u] ^ a[pa[u]]) * sz[u] voi root => reroot
*/