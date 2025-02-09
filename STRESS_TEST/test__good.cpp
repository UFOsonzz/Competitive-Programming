#include<bits/stdc++.h>
#define int long long
#define ii pair<int,int>

using namespace std;
const int maxn = 2e5 + 5;
int n, q, W;
array<int, 2> qr[maxn];
vector<int> adj[maxn];
vector<array<int, 2>> edges;
int lz[4 * maxn], b[maxn], in[maxn], out[maxn];
int cnt = 0;

struct node{
    int a, b, c, ab, bc, abc;
    node(int val = 0)
    {
        a = b = c = ab = bc = abc = val;
    }
    node operator + (node x) const
    {
        node z;
        if (a == -1e18) return x;
        if (x.a == -1e18) return (*this);
        z.a = max(a, x.a);
        z.b = max(b, x.b);
        z.c = max(c, x.c);
        z.ab = max({ab, x.ab, a + x.b});
        z.bc = max({bc, x.bc, b + x.c});
        z.abc = max({abc, x.abc, ab + x.c, a + x.bc});
        return z;
    }
};

node seg[4 * maxn];

inline void add(int id, int val)
{
    seg[id].a += val;
    seg[id].b -= 2 * val;
    seg[id].c += val;
    seg[id].ab -= val;
    seg[id].bc -= val;
    lz[id] += val;
}

inline void down(int id)
{
    if (lz[id] == 0) return;
    add(id * 2, lz[id]);
    add(id * 2 + 1, lz[id]);
    lz[id] = 0;
}

void upd(int lx, int rx, int val, int id = 1, int l = 1, int r = n * 2)
{
    if (lx > r || l > rx) return;
    if (lx <= l && r <= rx) return add(id, val);
    int mid = (l + r) / 2;
    down(id);
    upd(lx, rx, val, id * 2, l, mid);
    upd(lx, rx, val, id * 2 + 1, mid + 1, r);
    seg[id] = seg[id * 2] + seg[id * 2 + 1];
}

void dfs(int x = 1, int p = 1, int w = 0)
{
    in[x] = out[x] = ++cnt;
    for (int id : adj[x])
    {
        int i = edges[id][0] - x, w = edges[id][1];
        if (i == p) continue;
        b[id] = i;
        dfs(i, x, w);
        out[x] = ++cnt;
    }
    upd(in[x], out[x], w);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("test.inp", "r", stdin);
//    freopen("test.out", "w", stdout);
    cin >> n >> q >> W;
    for (int i = 1, u, v, w; i < n; i++)
    {
        cin >> u >> v >> w;
        if (u > v) swap(u, v);
        adj[u].emplace_back(edges.size());
        adj[v].emplace_back(edges.size());
        edges.push_back({u + v, w});
    }
    dfs();
    for (int i = 1, last = 0; i <= q; i++)
    {
        int id, w;
        cin >> id >> w;
        id = (id + last) % (n - 1);
        w = (w + last) % W;
        int x = b[id];
        upd(in[x], out[x], w - edges[id][1]);
        edges[id][1] = w;
        cout << (last = seg[1].abc) << "\n";
    }
}

