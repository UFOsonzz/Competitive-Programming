#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
struct edges{
    int u;
    int v;
    int w;
    bool operator<(const edges& other){
        return w < other.w;
    }
};
const int maxt = 20;
using pii = pair<int, int>;
int n, m, q, rep[200005], sz[200005], sparse[200005][23], depth[200005], gmax[200005][23]; vector<edges> edge;
vector<pii> adjlist[200005];
int find_set(int u){
    if (u == rep[u]) return u;
    return rep[u] = find_set(rep[u]);
}
void union_set(int u, int v){
    u = find_set(u); v = find_set(v);
    if (u != v){
        if (sz[u] < sz[v]) swap(u, v);
        rep[v] = u; sz[u] += sz[v];
    }
}
void dfs(int p, int u, int d){
    sparse[u][0] = p; depth[u] = d;
    for (auto c: adjlist[u]){
        if (c.fi != p) dfs(u, c.fi, d + 1), gmax[c.fi][0] = c.se;
    }
}
int lca(int u, int v){
    if (depth[u] < depth[v]) swap(u, v);
    int dis = depth[u] - depth[v]; int re = 0;
    for (int t = maxt; t >= 0; t--){
        if (dis & (1 << t)){
            re = max(re, gmax[u][t]);
            u = sparse[u][t];
        }
    }
    if (u == v) return re;
    for (int t = maxt; t >= 0; t--){
        if (sparse[u][t] != -1 && sparse[u][t] != sparse[v][t]){
            re = max(re, gmax[u][t]);
            re = max(re, gmax[v][t]);
            u = sparse[u][t]; v = sparse[v][t];
        }
    }
    re = max(re, gmax[u][0]); re = max(re, gmax[v][0]);
    return re;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m >> q;
    for (int i = 1;i <= m;i++){
        int u, v; cin >> u >> v;
        edge.push_back({u, v, i});
    }
    sort(edge.begin(), edge.end());
    for (int i = 1;i <= n;i++) rep[i] = i, sz[i] = 1;
    for (auto c: edge){
        if (find_set(c.u) != find_set(c.v)){
            adjlist[c.u].push_back({c.v, c.w});
            adjlist[c.v].push_back({c.u, c.w});
            union_set(c.u, c.v);
        }
    }
    memset(sparse, 255, sizeof sparse);
    for (int i = 1;i <= n;i++){
        if (i == find_set(i)){
            dfs(-1, i, 0);
        }
    }
    for (int t = 1; t <= maxt; t++){
        for (int i = 1;i <= n;i++){
            if (sparse[i][t - 1] != -1){
                sparse[i][t] = sparse[sparse[i][t - 1]][t - 1];
            }
        }
    }
    for (int t = 1; t <= maxt; t++){
        for (int i = 1;i <= n;i++){
            if (sparse[i][t - 1] != -1){
                gmax[i][t] = max(gmax[i][t - 1], gmax[sparse[i][t - 1]][t - 1]);
            }
        }
    }
    while (q--){
        int u, v; cin >> u >> v;
        if (find_set(u) != find_set(v)) cout << -1 << '\n';
        else cout << lca(u, v) << '\n';
    }
}
/*
    Canh lon nhat tren duong di giua 2 node trong cay khung nho nhat la nho nhat
*/