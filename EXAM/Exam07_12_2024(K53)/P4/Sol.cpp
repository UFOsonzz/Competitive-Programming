#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2505;
const int INF = 1e9;

int n, m;
vector<int> adj[MAXN];

int Shortest_Cycle(int root) {

    int d[MAXN], res = INF;
    queue<pair<int, int>> q;
    q.emplace(root, 0);

    for (int i = 1; i <= n; i++)
        d[i] = INF;
    
    d[root] = 0;

    while (!q.empty()) {
        int u = q.front().first;
        int fr = q.front().second;
        q.pop();
        
        for (auto c : adj[u]) {
            if (d[c] != INF) {
                if (c != fr) res = min(res, d[c] + d[u] + 1);
                continue;
            }

            d[c] = d[u] + 1;
            q.emplace(c, u);
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;

        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    int ans = INF;
    for (int i = 1; i <= n; i++)
        ans = min(ans, Shortest_Cycle(i)); // Shortest Cycle including i

    cout << (ans == INF ? -1 : ans);
}

// BFS tu tat ca cac dinh, den mot luc nao do (root -> v) (root -> u) (u -> v) se tao thanh mot chu trinh
// Luu y truong hop v nam tren duong di tu root -> u, de tranh truong hop do ta xem dinh tham truoc dinh u la dinh nao