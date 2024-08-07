#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 40;
int n, m, f[(1<<20)+2], g[(1<<20)+2], ori[(1<<20)+2];
ll adj[N+2];

vector<int> res;

int main() {
    //freopen("check.inp", "r", stdin);
    cin >> n >> m;
    for (int i = 0; i < n; i++) adj[i] = ((1LL<<n)-1)^(1LL<<i);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (adj[u]&(1LL<<v)) adj[u] ^= (1LL<<v);
        if (adj[v]&(1LL<<u)) adj[v] ^= (1LL<<u);
    }


    int fh = n/2, sh = n-fh;

    for (int i = 0; i < fh; i++) f[(1LL<<i)]=1;

    for (int i = 0; i < (1<<fh); i++) {
        ori[i]=i;
        if (!f[i]) continue;
        ll con = (1<<fh)-1;
        for (int j = 0; j < fh; j++)
        if (i&(1<<j)) con &= adj[j];

        for (int j = 0; j < fh; j++)
        if (!(i&(1<<j)) && (con&(1<<j)))
        f[i^(1<<j)] = max(f[i^(1<<j)], f[i]+1);

    }

    for (int i = 0; i < sh; i++) g[(1<<i)]=1;

    for (int i = 0; i < (1<<sh); i++) {
        if (!g[i]) continue;
        ll con = (1<<sh)-1;
        for (int j = 0; j < sh; j++)
        if (i&(1<<j)) con &= (adj[j+fh]>>fh);
        for (int j = 0; j < sh; j++)
        if (!(i&(1<<j)) && (con&(1<<j)))
        g[i^(1<<j)] = max(g[i^(1<<j)], g[i]+1);
    }

    for (int mask = 0; mask < (1<<fh); mask++)
    for (int i = 0; i < fh; i++) {
        if (mask&(1<<i))
        if (f[mask^(1<<i)] > f[mask]) {
            f[mask] = f[mask^(1<<i)];
            ori[mask] = ori[mask^(1<<i)];
        } else if (f[mask^(1<<i)] == f[mask]) {
            ori[mask] = min(ori[mask], ori[mask^(1<<i)]);
        }
    }

    int ans = 0;

    for (int mask = 0; mask < (1<<sh); mask++) {
        ll con = (1<<fh)-1;
        for (int i = 0; i < sh; i++)
        if (mask&(1<<i)) con &= adj[i+fh];
        ans = max(ans, g[mask]+f[con]);
    }
    bool flag = false;
    for (int mask = 0; mask < (1<<sh); mask++) {
        if (flag) break;
        ll con = (1<<fh)-1;

        for (int i = 0; i < sh; i++)
        if (mask&(1<<i)) con &= adj[i+fh];
        if (g[mask]+f[con]==ans) {
            assert(__builtin_popcount(mask)+__builtin_popcount(ori[con]) == ans);
            //cout << ans << '\n';
            for (int j = 0; j < sh; j++)
            if (mask&(1<<j)) res.push_back(j+fh);
            for (int j = 0; j < fh; j++)
            if (ori[con]&(1<<j)) res.push_back(j);
            flag = true;
            break;
        }
    }
    cout << res.size() << '\n';
    for (auto c: res) cout << c << " ";
}