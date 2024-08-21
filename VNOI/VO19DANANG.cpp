#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Edge = pair<int, int>;
using Container = tuple<long long, int, int>;

#define fi first
#define se second

const int MAXN = 2e5;
const int INF = 1e9;

int n, m, d;

vector<Edge> adj[MAXN + 5];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m >> d;

    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }
    
    for (int i = 1; i <= n; i++)
        sort(adj[i].begin(), adj[i].end(), [&](Edge u, Edge v) {
            return u.se < v.se;
        });

    priority_queue<Container, vector<Container>, greater<Container>> pq;

    pq.emplace(0, 1, -INF);

    while (!pq.empty()) {
        ll D;
        int u, e;

        tie(D, u, e) = pq.top();
        pq.pop();

        if (u == n) return cout << D, 0;

        while (!adj[u].empty() && e + d <= adj[u].back().se) {
            auto Back = adj[u].back();
            auto Temp = make_tuple(D + Back.se, Back.fi, Back.se);

            adj[u].pop_back();
            pq.push(Temp);
        }
    }

    cout << -1;
}

/*
    Dijkstra canh, vi canh hien tai luon duoc co dinh nen khong can luu mang dis boi vi khi push vao pq luon dam bao la nho nhat roi
*/