#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int N = 2e5 + 5;
int n, m, a[N], pv[N];

ll seg[4*N], lazy[4*N];
map<int, int> pre;
void add(ll &x, ll y) {
    x += y;
    if (x >= mod) x -= mod;
}

void push(int root, int tl, int tr, ll v) {
    add(seg[root], 1LL * (tr - tl + 1) * v % mod);
    add(lazy[root], v);
}

void update(int root, int tl, int tr, int l, int r, ll v) {
    if (tl > r || tr < l || l > r) return;
    if (tl >= l && tr <= r) {
        push(root, tl, tr, v);
        return;
    }

    int tm = (tl + tr) / 2;
    push(2*root, tl, tm, lazy[root]);
    push(2*root+1, tm+1, tr, lazy[root]);
    lazy[root] = 0;

    update(2*root, tl, tm, l, r, v);
    update(2*root+1, tm+1, tr, l, r, v);
    seg[root] = (seg[2*root] + seg[2*root + 1]) % mod;
}

ll get(int root, int tl, int tr, int l, int r) {
    if (tl > r || tr < l || l > r) return 0;
    if (tl >= l && tr <= r) return seg[root];
    int tm = (tl + tr) / 2;
    push(2*root, tl, tm, lazy[root]);
    push(2*root+1, tm+1, tr, lazy[root]);
    lazy[root] = 0;
    return (get(2*root, tl, tm, l, r) + get(2*root+1, tm+1, tr, l, r)) % mod;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("candyroad.inp", "r", stdin);
    // freopen("candyroad.out", "w", stdout);
    cin >> n >> m;
    ll total = 1LL * m * (m + 1) / 2;
    total %= mod;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (pre.find(a[i]) != pre.end()) pv[i] = pre[a[i]];
        pre[a[i]] = i;
    }
    total %= mod;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        update(1, 1, n, pv[i] + 1, i, a[i]);
        ans += (total * (ll)i % mod - get(1, 1, n, 1, i) + mod) % mod;
        // cout << i << " " << (total * i % mod - get(1, 1, n, 1, i) + mod) % mod << '\n';
        ans %= mod;
    }

    cout << ans;
}