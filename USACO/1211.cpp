#include<bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define fi first
#define se second

const int N = 1e6 + 5;

int n, pos[N][15];
pii near[15];
ll ans = 0;

struct Edge {
    ll c;
    int u, v;

    Edge(ll _c, int _u, int _v): 
        c(_c), u(_u), v(_v) {};
};

struct Dsu {
    vector<int> par;

    void init(int n) {
        par.resize(n + 5, 0);
        for (int i = 1; i <= n; i++) par[i] = i;
    }

    int find(int u) {
        if (par[u] == u) return u;
        return par[u] = find(par[u]);
    }

    bool join(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        par[v] = u;
        return true;
    }
} dsu;

vector<Edge> edges;

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        pos[x][y] = i;
    }

    memset(near, -1, sizeof(near));

    for(int x = 0; x <= 1e6; x++) {

        pii tmp = {-1, -1};
        for (int y = 0; y <= 10; y++) {

            if (pos[x][y] == 0)
                continue;

            if (tmp.fi != -1)
                edges.emplace_back(1LL * (y - tmp.se) * (y - tmp.se), tmp.fi, pos[x][y]);

            tmp = {pos[x][y], y};

            for (int j = 0; j <= 10; j++)
                if (near[j].fi != -1)
                    edges.emplace_back(1LL * (y - j) * (y - j) + 1LL * (x - near[j].se) * (x - near[j].se), near[j].fi, pos[x][y]);

            near[y] = {pos[x][y], x};
        }
    }

    dsu.init(n);

    sort(edges.begin(), edges.end(), [&](Edge x, Edge y) {
        return x.c < y.c;
    });

    for (auto e : edges)
        if (dsu.join(e.u, e.v))
            ans += e.c;

    cout << ans;
}

/*
    BOT CANH THEO KRUSKAL : 
        TRONG TAM GIAC TU THI CANH DOI DIEN VOI GOC TU LUON LA LON NHAT
        GIA SU CANH BC LON NHAT TRONG TAM GIAC ABC
        => KHI KRUSKAL THI AB, AC DEU DUOC XET TRUOC BC
        => XET DEN BC THI A LIEN THONG B LIEN THONG C ROI => BC KHONG BAO GIO LA CANH CUA CAY KHUNG NN => LOAI
*/
