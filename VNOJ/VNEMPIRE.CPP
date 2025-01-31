#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

struct Planet {
    int x, y, z;
    Planet() {}
    Planet(int x, int y, int z) :
        x(x), y(y), z(z) {}
} pln[MAXN];

int n, pa[MAXN];
vector<tuple<int, int, int>> edges;
vector<pair<int, int>> coor[3];

int find_set(int u) {
    if (u == pa[u])
        return u;
    return pa[u] = find_set(pa[u]);
}

bool union_set(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if (u == v)
        return false;
    pa[v] = u;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        pln[i] = {x, y, z};
        coor[0].emplace_back(x, i);
        coor[1].emplace_back(y, i);
        coor[2].emplace_back(z, i);
    }

    for (int i = 0; i < 3; i++)
        sort(coor[i].begin(), coor[i].end());

    for (int i = 0; i < 3; i++) {
        for (int j = 1; j < coor[i].size(); j++) {
            int dist = coor[i][j].first - coor[i][j - 1].first;
            int plnx = coor[i][j].second;
            int plny = coor[i][j - 1].second;
            edges.emplace_back(dist, plnx, plny);
        }
    }

    sort(edges.begin(), edges.end());

    for (int i = 1; i <= n; i++)
        pa[i] = i;

    long long mst = 0;
    for (auto c : edges) {
        int d, x, y;
        tie(d, x, y) = c;
        if (union_set(x, y)) 
            mst += d;
    }

    cout << mst;
}

/*
    y tuong dua tren thuat toan kruskal :
        xet rieng toan do x, co 3 thang a1.x < a2.x < a3.x
        kruskal se khong bao gio accept canh a1.x -> a3.x vi co the lien thong a1, a3 bang a1.x -> a2.x va a2.x -> a3.x
        => chi xet cac canh tao boi cac toa do lien tiep -> 3n canh
*/