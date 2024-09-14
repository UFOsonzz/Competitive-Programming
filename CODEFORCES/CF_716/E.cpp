#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;

#define fi first
#define se second

const int MAXN = 1e5;

int n, m, phi;
vector<pii> adj[MAXN + 5];
ll T[MAXN + 5], inv[MAXN + 5], ans;

ll Exp(ll a, int b) {
    if (b == 0) return 1LL;

    ll tmp = Exp(a, b / 2);
    tmp = (tmp * tmp) % m;

    if (b & 1) tmp = tmp * a % m;
    return tmp;
}

int sz[MAXN + 5];
bool Selected[MAXN + 5];

int dfs_sz(int p, int u) {
    sz[u] = 1;
    for (auto c: adj[u]) {
        if (c.fi == p || Selected[c.fi]) continue;
        sz[u] += dfs_sz(u, c.fi);
    }

    return sz[u];
}

int get_centroid(int p, int u, int s) {
    for (auto c: adj[u]) {
        if (c.fi == p || Selected[c.fi]) continue;
        if (sz[c.fi] * 2 > s) 
            return get_centroid(u, c.fi, s);
    }

    return u;
}

int neg = 0;
map<ll, int> mp;
vector<ll> upd;

void Clear_data(int neg_val) {
    neg = neg_val;
    mp.clear();
    mp[0] = 1;
}

void dfs_ans(int p, int u, int dep, ll x, ll g, bool Rev_loop) {
    for (int i = 0; i < adj[u].size(); i++) {
        int idx = (!Rev_loop ? i : (int)adj[u].size() - 1 - i);

        pii c = adj[u][idx];

        if (c.fi == p || Selected[c.fi]) continue;

        ll new_x = (x + T[dep] * c.se) % m;
        ll new_g = (10 * g + c.se) % m;
        ll v = (m - new_g) * inv[dep + 1] % m;

        ans += (!new_x && neg);

        if (mp.find(v) != mp.end())
            ans += mp[v] - (!v && neg);

        upd.push_back(new_x);
        dfs_ans(u, c.fi, dep + 1, new_x, new_g, Rev_loop);

        if (dep == 0) {
            for (auto v: upd) mp[v]++;
            upd.resize(0);
        }
    }
    
}

void centroid(int u) {
    int s = dfs_sz(0, u);
    int C = get_centroid(0, u, s);

    Clear_data(0);
    dfs_ans(0, C, 0, 0, 0, false);

    Clear_data(1);
    dfs_ans(0, C, 0, 0, 0, true);

    Selected[C] = true;

    for (auto c: adj[C]) 
        if (!Selected[c.fi]) centroid(c.fi);

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        ++u; ++v;

        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    phi = 1;
    int tmp = m;

    for (int i = 2; i * i <= m; i++) {
        if (tmp % i == 0) {
            while (tmp % i == 0)
                phi *= i, tmp /= i;

            phi = phi / i * (i - 1);
        }
    }

    if (tmp > 1) phi *= (tmp-1);
    T[0] = (1 % m);

    for (int i = 1; i <= MAXN; i++) {
        T[i] = T[i-1] * 10 % m;
        inv[i] = Exp(T[i], phi - 1);
    }

    centroid(1);
    cout << ans;
}
/*
    Xet toan bo duong di bang centroid
    gia su hien tai duyet duong mot duong di tu goc centroid co gia tri x va x co d digit, ta can dem so duong di (reverse theo huong di tu dinh u den goc centroid) co gia tri :
    y * 10 ^ d + x dong du 0 mod M --> y dong du (M - x) * inv[10 ^ d] mod M
    lai co (M, 10) = 1 --> (M, 10 ^ x) = 1 --> ton tai inv[10 ^ x];
    theo dinh ly phi ham euler ta co : 
    (10 ^ x) ^ phi(M) dong du 1 mod M
    vi (M, 10 ^ x) nen :
    (10 ^ x) ^ (phi(M) - 1) dong du inv[10 ^ x] mod M
    --> inv[10 ^ x] = (10 ^ x) ^ (phi(M) - 1)
*/