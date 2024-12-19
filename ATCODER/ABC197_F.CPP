#include <bits/stdc++.h>

using namespace std;
using Tri = tuple<int, int, int>;

const int MAXN = 1005;
const int INF = 1e9;

struct Edge {
    int u, v;
    char w;

    Edge() {}
    Edge(int u, int v, char w) :
        u(u), v(v), w(w) {}
} Ed[MAXN];

int n, m, d[MAXN][MAXN];
vector<int> adj[MAXN][30];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        char w;
        cin >> u >> v >> w;
        Ed[i] = {u, v, w};

        adj[u][w - 'a'].push_back(i);
        adj[v][w - 'a'].push_back(i);
    }

    priority_queue<Tri, vector<Tri>, greater<Tri>> pq;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            d[i][j] = INF;
    
    for (int i = 1; i <= m; i++) {
        int u = Ed[i].u;
        int v = Ed[i].v;

        d[u][v] = d[v][u] = 1;
        pq.emplace(1, u, v);
        pq.emplace(1, v, u);
    }


    for (int i = 1; i <= n; i++) {
        d[i][i] = 0;
        pq.emplace(0, i, i);
    }

    int ans = INF;

    while (!pq.empty()) {
        int dis, u, v;
        tie(dis, u, v) = pq.top();
        pq.pop();

        if (dis > d[u][v]) 
            continue;

        for (int ch = 0; ch < 26; ch++) {
            for (auto idu : adj[u][ch]) {
                int nxtu = Ed[idu].u + Ed[idu].v - u;
                for (auto idv : adj[v][ch]) {
                    int nxtv = Ed[idv].u + Ed[idv].v - v;
                    
                    if (d[nxtu][nxtv] > d[u][v] + 2) {
                        d[nxtu][nxtv] = d[u][v] + 2;
                        pq.emplace(d[nxtu][nxtv], nxtu, nxtv);
                    } 
                }
            }
        }
    }

    ans = min({ans, d[1][n], d[n][1]});

    cout << (ans == INF ? -1 : ans);
}

/*
    hinh dung co 2 nguoi : 
        1 nguoi di tu dinh 1
        1 nguoi di tu dinh n
        2 nguoi cung di chuyen tung buoc tren cac canh co cung chu cai

    goi dp[i][j] : la duong di ngan nhat de xay duoc mot palindrome ma hien tai nguoi 1 o i, nguoi 2 o j
    => dp[i][j] -> dp[ni][nj] khi va chi khi canh (i, ni) co chu cai = chu cai cua canh (j, nj)
    so canh phai duyet la so cap canh co cung chu cai (max = m^2)
    dijkstra tu cac trang thai dp[i][i] va dp[i][j] sao cho co canh noi tu i den j
    ket qua la dp[1][n] (hoac dp[n][1])
*/