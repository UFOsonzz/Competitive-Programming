#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
const int M = 5e5 + 5;
int n, m, a, b, sz[N], low[N], num[N];
long long oka, okb;
vector<int> adj[N];

void dfs(int u) {
    num[u] = ++num[0];
    sz[u] = 1;
    low[u] = num[u];
    for (auto c : adj[u]) {
        if (sz[c] != 0) {
            low[u] = min(low[u], num[c]);
            continue;
        }

        dfs(c);
        if (!low[0] && u == a && num[b]) {
            low[0] = 1;
            oka = n - 1 - sz[c];
        }
        
        if (low[c] >= num[u] && u == b) {
            okb += sz[c];
        }

        sz[u] += sz[c];
       

        low[u] = min(low[u], low[c]);
    }
}


void solve() {
    cin >> n >> m >> a >> b;
    for (int i = 1; i <= n; i++)
        adj[i].clear(), sz[i] = num[i] = 0;
    num[0] = oka = okb = low[0] = 0;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs(a);
    if (a != b) 
        cout << oka * okb << '\n';
    else cout << okb << '\n';
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
y tuong: 
cay dfs, co dinh root cay dfs o a, khi do cac cap thoa man se la (u, v)
trong do u la cac thang trong cay khong thuoc nhanh con cua root chua b
v la cac thang trong cay con goc b sao cho:
nhanh cua cay con goc b chua thang nay khong ton tai canh nguoc di len tren dinh b
*/