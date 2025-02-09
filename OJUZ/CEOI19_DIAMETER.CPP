#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1e5 + 5;
const int LG = 20;
const ll INF = 2e18;

int n, q, sz[MAXN], head[MAXN], pa[MAXN], in[MAXN], out[MAXN], trace[MAXN];
ll limW;
vector<int> adj[MAXN], dfs_order;

struct Edge {
    int u, v;   
    ll w;

    Edge() {}
    Edge(int u, int v, ll w) :
        u(u), v(v), w(w) {}

} edges[MAXN];

struct Segment_Tree {
    ll *seg, *lazy;
    Segment_Tree(int n) : 
        seg(new ll[4 * n]),
        lazy(new ll[4 * n]) {
            memset(seg, 0, sizeof(ll) * 4 * n);
            memset(lazy, 0, sizeof(ll) * 4 * n);
        }

    void push(int root, ll val) {
        seg[root] += val;
        lazy[root] += val;
    }

    void update(int root, int tl, int tr, int l, int r, ll val) {
        if (tl > r || tr < l)
            return;
        if (tl >= l && tr <= r) {
            push(root, val);
            return;
        }

        int tm = (tl + tr) / 2;
        push(2 * root, lazy[root]);
        push(2 * root + 1, lazy[root]);
        lazy[root] = 0;

        update(2 * root, tl, tm, l, r, val);
        update(2 * root + 1, tm + 1, tr, l, r, val);
        seg[root] = max(seg[2 * root], seg[2 * root + 1]);
    }

    ll get(int root, int tl, int tr, int l, int r) {
        if (tl > r || tr < l || l > r)
            return -INF;
        if (tl >= l && tr <= r) 
            return seg[root];
        
        int tm = (tl + tr) / 2;
        push(2 * root, lazy[root]);
        push(2 * root + 1, lazy[root]);
        lazy[root] = 0;

        return max(get(2 * root, tl, tm, l, r),
            get(2 * root + 1, tm + 1, tr, l, r));
    }

    int get_maxid(int root, int tl, int tr) {
        if (tl == tr)
            return trace[tl];
        int tm = (tl + tr) / 2;

        push(2 * root, lazy[root]);
        push(2 * root + 1, lazy[root]);
        lazy[root] = 0;

        if (seg[2 * root] > seg[2 * root + 1])
            return get_maxid(2 * root, tl, tm);
        else return get_maxid(2 * root + 1, tm + 1, tr);
    }
} Find_u(MAXN), Find_v(MAXN);

void dfs_sz(int p, int u) {
    pa[u] = p;
    sz[u] = 1;

    for (auto& id : adj[u]) {
        int v = edges[id].u + edges[id].v - u;
        if (v == p) {
            id = p;
            continue;
        }

        dfs_order.push_back(id);

        dfs_sz(u, v);
        sz[u] += sz[v];
        id = v;
        if (sz[v] > sz[adj[u][0]])
            swap(id, adj[u][0]);
    }

    for (int i = 0; i < adj[u].size(); i++) {
        if (adj[u][i] == p) {
            adj[u].erase(adj[u].begin() + i);
            return;
        }
    }
}

void dfs_head(int u) {
    in[u] = ++in[0];
    trace[in[u]] = u;

    if (u == 1)
        head[u] = u;

    for (int i = 0; i < adj[u].size(); i++) {
        if (i == 0) 
            head[adj[u][i]] = head[u];
        else head[adj[u][i]] = adj[u][i];

        dfs_head(adj[u][i]);
    }

    out[u] = in[0];
}

void update(int u, ll diff) {
    Find_u.update(1, 1, n, in[u], out[u], diff);
    Find_v.update(1, 1, n, in[u], out[u], -diff);

    while (u != 0) {
        u = head[u];
        int p = pa[u];
        if (p != 0) {
            int heavy_in = in[adj[p][0]];
            int heavy_out = out[adj[p][0]];
            ll max_valv = max(Find_u.get(1, 1, n, in[p], heavy_in - 1),
                            Find_u.get(1, 1, n, heavy_out + 1, out[p]));
            
            ll p_valv = Find_v.get(1, 1, n, in[p], in[p]);
            ll upd_valv = max_valv - 2 * Find_u.get(1, 1, n, in[p], in[p]) - p_valv;
            Find_v.update(1, 1, n, in[p], in[p], upd_valv);
        }

        u = p;
    }
}

ll get_v(int u) {
    ll ans = 0;

    while (u != 0) {
        ans = max(ans, Find_v.get(1, 1, n, in[head[u]], in[u] - 1));
        u = head[u];
        int p = pa[u];
        if (p != 0) {
            int heavy_in = in[u];
            int heavy_out = out[u];
            ll max_valv = max(Find_u.get(1, 1, n, in[p], heavy_in - 1),
                            Find_u.get(1, 1, n, heavy_out + 1, out[p]));

            ans = max(ans, max_valv - 2 * Find_u.get(1, 1, n, in[p], in[p]));
        }

        u = p;
    }

    return ans;
}

ll find_diameter() {
    int u = Find_u.get_maxid(1, 1, n);
    return Find_u.get(1, 1, n, in[u], in[u]) + get_v(u);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> q >> limW;

    for (int i = 1; i < n; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
        adj[u].push_back(i);
        adj[v].push_back(i);
    }

    dfs_sz(0, 1);
    dfs_head(1);

    for (int i = 1; i < n; i++) {
        if (edges[i].u == pa[edges[i].v])
            swap(edges[i].u, edges[i].v);
    }

    for (auto i : dfs_order) 
        update(edges[i].u, edges[i].w);

    ll last = 0;
    while (q--) {
        ll dj, ej;
        cin >> dj >> ej;
        dj = (dj + last) % (n - 1) + 1;
        ej = (ej + last) % limW;
        update(edges[dj].u, ej - edges[dj].w);
        edges[dj].w = ej;
        last = find_diameter();

        cout << last << '\n';
    }
}

/*
    Y tuong tu thuat toan tim duong kinh : 
    phase 1 : tim thang xa goc nhat sau moi lan cap nhat (cai nay de)
    phase 2 : tu thang vua tim duoc, tim thang xa thang do nhat
    goi dis la khoang cach tu goc den dinh (dis[])
    y tuong ban dau : voi moi node u luu max dis[x thuoc cay con] - 2dis[u] xong hld
    -> bi trung
    giai quyet phan bi trung : 
    voi moi node u luu max dis[x thuoc cac cay con nhanh light] - 2dis[u]
    luc cap nhat : 
    update dis[u] voi toan bo cay con goc u xong walk tu u len theo hld, khong cap nhat cac dinh trong chain vi u thuoc nhanh heavy cua bon no
    voi nhung dinh dau moi chain goi la c (u la con light cua dinh nay) : ta tinh lai dis[x thuoc cay con light] - 2dis[c] bang cach
    get 2 doan thua ra khi xoa doan con lien tiep trong euler tour la cay con heavy [/////////xxxxxxxx//////] xong lay max
    luc lay ket qua : 
    voi moi thang trong chain thi chi can get binh thuong khong bi trung vi u thuoc nhanh heavy
    voi nhung thang dau chuoi thi goi la c (u la con light) : ta get 2 doan thua ra khi xoa doan con lien tiep trong euler tour la cay con chua u
    [///////xxxxxx////]
*/