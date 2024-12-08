// Credit : Someone on Vjudge ;-;
#include <bits/stdc++.h>
#define task ""
#define ll long long
#define ld long double
#define fi first
#define se second
#define pb push_back
using namespace std;
const int maxn = 1e6 + 5;
const ll INF = 1e18 + 5;
int n, q;
vector<int> g[maxn];
bool visit[maxn] = {false};
int up[maxn][20], h[maxn];

void dfs(int u) {
    for (int v : g[u]) {
        if (v == up[u][0]) continue;
        h[v] = h[u] + 1;

        up[v][0] = u;
        for (int j = 1; j < 20; ++j)
            up[v][j] = up[up[v][j - 1]][j - 1];

        dfs(v);
    }
}

int lca(int u, int v) {
    if (h[u] != h[v]) {
        if (h[u] < h[v]) swap(u, v);

        // Tìm tổ tiên u' của u sao cho h(u') = h(v)
        int k = h[u] - h[v];
        for (int j = 0; (1 << j) <= k; ++j)
            if (k >> j & 1) // Nếu bit thứ j của k là 1
                u = up[u][j];
    }

    if (u == v) return u;

    // Tìm lca(u, v)
    int k = __lg(h[u]);
    for (int j = k; j >= 0; --j)
        if (up[u][j] != up[v][j]) // Nếu tổ tiên thứ 2^j của u và v khác nhau
            u = up[u][j], v = up[v][j];
    return up[u][0];
}

void Input() {
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    cin >> q;
}

void Solve() {
    int r, u, v;
    cin >> r >> u >> v;
    int x = lca(r, u),
        y = lca(r, v),
        z = lca(u, v);
    if (x == y) return cout << z << '\n', void();

    if(abs(h[x] - h[r]) < abs(h[y] - h[r]))
        cout << x << '\n';
    else
        cout << y << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Input();
    dfs(1);
    while(q--)
        Solve();
}

/*
    goi L = lca(u, v)
    xet 3 truong hop : 
    r nam ngoai cay con goc L => lca moi la L
    r nam tren duong di (u -> v) => lca moi la r
    r nam trong cay con goc L nhung khong nam tren duong di (u -> v)   
        => binary jumping cho den khi gap mot dinh thuoc duong di (u -> v) -> dinh do chinh la lca moi

*/