#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
const int LG = 20;

int n, k, sp[MAXN][LG], depth[MAXN];
vector<int> adj[MAXN], meeting[MAXN];

void dfs(int p, int u) {
    depth[u] = depth[p] + 1;

    for (auto c : adj[u]) {
        if (c == p)
            continue;
        dfs(u, c);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) 
        swap(u, v);

    int diff = depth[u] - depth[v];

    for (int t = LG - 1; t >= 0; t--)
        if (diff >> t & 1)
            u = sp[u][t];

    if (u == v)
        return u;

    for (int t = LG - 1; t >= 0; t--)
        if (sp[u][t] != sp[v][t])
            u = sp[u][t], v = sp[v][t];

    return sp[u][0];
}

int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    
    int root;
    for (int i = 1; i <= n; i++) {
        int attend, par;
        cin >> attend >> par;
        if (par == 0)
            root = i;
        else {
            adj[par].push_back(i);
            sp[i][0] = par;
        }

        meeting[attend].push_back(i);
    }

    for (int t = 1; t < LG; t++)
        for (int i = 1; i <= n; i++)
            sp[i][t] = sp[sp[i][t - 1]][t - 1];

    dfs(0, root);

    for (int meet = 1; meet <= k; meet++) {
        int src = meeting[meet][0];
        int new_src, max_dist = -1;

        for (auto c : meeting[meet]) {
            if (dist(src, c) > max_dist) {
                max_dist = dist(src, c);
                new_src = c;
            }
        }

        max_dist = -1;

        for (auto c : meeting[meet]) 
            if (dist(new_src, c) > max_dist)
                max_dist = dist(new_src, c);

        cout << max_dist << '\n';
    }   
}

/*
    y tuong cua bai dua tren thuat toan tim duong kinh cua cay : 
        tu mot dinh bat ky tim dinh xa no nhat
        tu dinh xa nhat do tim dinh xa no nhat
        => khoang cach giua 2 thang nay chinh la duong kinh
    ap dung : 
        voi moi tap meeting : 
            chon mot thang goc bat ky roi tim thang xa no nhat
            tu thang vua tim duoc tim thang xa no nhat
            => max_dist trong mot meeting
*/