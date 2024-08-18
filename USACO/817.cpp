#include <bits/stdc++.h>
using namespace std;
using Query = pair<char, int>;
using pii = pair<int, int>;

#define fi first
#define se second

const int MAXN = 1e5;
const int LG = 18;

int q, jump[MAXN + 5][LG + 1], dsu_id[MAXN + 5], depth[MAXN + 5];
pii diameter[MAXN + 5];
vector<Query> qr;

int find_dsu(int u) {
    if (u == dsu_id[u]) return u;
    return dsu_id[u] = find_dsu(dsu_id[u]);
}

bool union_dsu(int u, int v) {
    u = find_dsu(u);
    v = find_dsu(v);

    if (u == v) return false;

    dsu_id[v] = u;
    return true;
}

int get_dist(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    int depth_diff = depth[u] - depth[v];
    int cur_dist = 0;

    for (int i = LG - 1; i >= 0; i--) {
        if (depth_diff >> i & 1) {
            cur_dist += 1 << i;
            u = jump[u][i]; 
        }
    }

    if (u == v) return cur_dist;

    for (int i = LG - 1; i >= 0; i--) {
        if (jump[u][i] != jump[v][i]) {
            cur_dist += 1 << i + 1;
            u = jump[u][i];
            v = jump[v][i];
        }
    }

    return cur_dist + 2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);

    cin >> q;
    
    int cnt = 0;

    for (int i = 1; i <= q; i++) {
        char typ;
        int node;
        cin >> typ >> node;
        
        if (typ == 'B') {
            ++cnt;
            if (node != -1) {
                jump[cnt][0] = node;
                depth[cnt] = depth[node] + 1;
            }
        }

        qr.emplace_back(typ, node);
    }

    for (int g = 1; g < LG; g++) 
        for (int i = 1; i <= cnt; i++) 
            jump[i][g] = jump[jump[i][g - 1]][g - 1];
        
    for (int i = 1; i <= cnt; i++)
        dsu_id[i] = i, diameter[i] = {-1, -1};
    
    for (int i = 1; i <= cnt; i++) 
        if (jump[i][0]) union_dsu(i, jump[i][0]);

    cnt = 0;
    for (auto& c : qr) {
        if (c.fi == 'B') {
            int dsu = find_dsu(++cnt);
            if (c.se == -1) diameter[dsu] = {cnt, cnt};
            else {
                int dia = get_dist(diameter[dsu].fi, diameter[dsu].se);
                if (get_dist(diameter[dsu].fi, cnt) > dia)
                    diameter[dsu].se = cnt;
                else if (get_dist(cnt, diameter[dsu].se) > dia) diameter[dsu].fi = cnt;
            }
        } else {
            int dsu = find_dsu(c.se);

            cout << max(get_dist(diameter[dsu].fi, c.se), get_dist(c.se, diameter[dsu].se)) << '\n';
        }
    }
}

/*
    Voi moi cay, ta duy tri duong kinh cua cay, duong di dai nhat bat dau tu mot dinh u chac chan co mot dau la 1 trong 2 dau cua duong kinh hien tai
    Ta tinh khoang cach giua cac dinh bang cach build cay truoc roi nhay lca, luu lai cac truy van roi lam sau khi build xong khoang cach va dsu_id thi xu ly
*/