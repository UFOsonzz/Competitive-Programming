#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 505;
const int B = 315;


int n, m, q;
ll a[MAXN][MAXN], p[MAXN][MAXN], d[MAXN][MAXN];

vector<tuple<int, int, ll>> Query;

ll fix(int x, int y) {

    ll res = p[x][y];
    for (auto c : Query) {
        int cx, cy; ll cw;
        tie(cx, cy, cw) = c;

        if (cx <= x && cy <= y) 
            res += cw * (x - cx + 1) * (y - cy + 1);
    }

    return res;
}

ll get_rec(int x, int y, int u, int v){
    return fix(u, v) - fix(x - 1, v) -  fix(u, y - 1) + fix(x - 1, y - 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m >> q;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            p[i][j] = p[i][j - 1] + p[i - 1][j]- p[i - 1][j - 1] + a[i][j];
        }
    }

    while (q--) {
        if (q % B == 0) {

            memset(d, 0, sizeof d);
            for (auto c: Query) {
                int cx, cy; ll cw;
                tie(cx, cy, cw) = c;
                d[cx][cy] += cw;
            }

            Query.clear();

            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];
                    a[i][j] += d[i][j];
                    p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + a[i][j];
                }
            }
        }

        int c; 
        cin >> c;

        if (c == 1) {
            int x, y, u, v; ll w;
            cin >> x >> y >> u >> v >> w;

            Query.emplace_back(x, y, w);
            Query.emplace_back(x, v + 1, -w);
            Query.emplace_back(u + 1, y, -w);
            Query.emplace_back(u + 1, v + 1, w);

        } else {

            int x, y, u, v;
            cin >> x >> y >> u >> v;
            cout << get_rec(x, y, u, v) << '\n';
        }
    }

}

/*
    Chia can truy van : 
        sau can truy van cap nhat lai mot lan
        khi tra loi mot truy van luc chua cap nhat day du : 
            duyet nhung truy van chua duoc cap nhat (<= B truy van)
            voi moi truy van do ta biet duoc no dong gop bao nhieu cho ket qua hien tai
                => tinh duoc truy van hien tai
        
        cap nhat lai bang sau can truy van 
*/