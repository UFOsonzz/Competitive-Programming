//#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

#define eb emplace_back
#define fi first
#define se second

const int N = 1e5 + 5;
const int B = 450;

int n, q, in[N], out[N], v[2*N], sp[N][20], dep[N], res[N], ori[2*N];

vector<pii> adj[N];

void dfs(int p, int u){
    in[u] = ++in[0];
    sp[u][0] = p;
    dep[u] = dep[p] + 1;
    for (auto c: adj[u]){
        if (c.fi == p) continue;
        dfs(u, c.fi);
        v[in[c.fi]] = v[out[c.fi]] = c.se;
    }
    out[u] = ++in[0];
}

int lca(int u, int v){
    if (dep[u] < dep[v]) swap(u, v);
    int dis = dep[u] - dep[v];
    for (int i = 0; i <= 18; i++)
        if ((dis >> i) & 1)
            u = sp[u][i];
    if (u == v) return u;
    for (int i = 18; i >= 0; i--)
        if (sp[u][i] != sp[v][i] && sp[u][i])
            u = sp[u][i], v = sp[v][i];
    return sp[u][0];
}

struct Que {
    int l, r, id;
    bool operator<(const Que& other){
        if (l / B == other.l / B)
            return r < other.r;
        return l / B < other.l / B;
    }
} query[N];
bitset<N> bs;
int pre[N];

void add(int x){
    if (v[x] > n) return;
    in[ori[x]]++;
    if (in[ori[x]] == 2){
        pre[v[x]]--;
        if (!pre[v[x]]) bs[v[x]] = 1;
        return;
    }
    pre[v[x]]++;
    if (pre[v[x]] == 1) bs[v[x]] = 0;
}

void era(int x){
    if (v[x] > n) return;
    in[ori[x]]--;
    if (in[ori[x]] > 0){
        pre[v[x]]++;
        if (pre[v[x]] == 1) bs[v[x]] = 0;
        return;
    }
    pre[v[x]]--;
    if (!pre[v[x]]) bs[v[x]] = 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> q;
    for (int i = 1; i < n; i++){
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].eb(v, c);
        adj[v].eb(u, c);
    }
    dfs(0, 1);
    for (int t = 1; t <= 18; t++)
        for (int i = 1; i <= n; i++)
            if (sp[i][t - 1])
                sp[i][t] = sp[sp[i][t - 1]][t - 1];
    for (int i = 1; i <= q; i++){
        query[i].id = i;
        int u, v; cin >> u >> v;
        if (in[u] > in[v]) swap(u, v);
        int cha = lca(u, v);
        if (cha != u && cha != v){
            query[i].l = out[u];
            query[i].r = in[v];
        }else{
            query[i].r = in[v];
            int dis = dep[v] - dep[u] - 1;
            for (int j = 0; j <= 18; j++)
                if ((dis >> j) & 1)
                    v = sp[v][j];
            query[i].l = in[v];
        }
    }
    sort(query + 1, query + 1 + q);
    for (int u = 1; u <= n; u++)
        ori[in[u]] = ori[out[u]] = u;
    v[in[1]] = v[out[1]] = 1e9;
    memset(in, 0, sizeof in);
    bs.set();
    int L = 1, R = 1;
    add(1);
    for (int i = 1; i <= q; i++){

        if (R > query[i].r){
            for (; R > query[i].r; R--)
                era(R);
        }else if (R < query[i].r){
            do{
                R++;
                add(R);
            }while(R < query[i].r);
        }
        if (L > query[i].l){
            do{
                L--;
                add(L);
            }while (L > query[i].l);
        }else if (L < query[i].l)
            for (; L < query[i].l; L++)
                era(L);
        res[query[i].id] = bs._Find_first();
    }
    for (int i = 1; i <= q; i++)
        cout << res[i] << '\n';

}
/*
    Mo tren cay: 
    Trai cay thanh duong thang theo thu tu Euler tour kieu mot dinh xuat hien 2 lan :>
    voi 2 dinh (u, v) neu u la to tien v -> truy van [in[u], in[v]]
    neu u ko phai to tien v -> truy van [out[u], in[v]] + [in[lca], in[lca]] (trong bai nay la xet canh nen ko can xet in[lca])
    Phan lay ket qua : 
    Duy tri mot mang ap[] xem mot node xuat hien bao nhieu lan, chan lan thi ko tinh, le moi tinh
    Dem bang bitset (_Find_first()) (ngoai ra con nhieu cach khac)
*/