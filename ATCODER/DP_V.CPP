#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1e5 + 5;

int n;
ll mod, ddp[MAXN], udp[MAXN];
vector<int> adj[MAXN];

void Calc_ddp(int u, int p) {

    ddp[u] = 1;
    int par_id = -1;

    for (int i = 0; i < adj[u].size(); i++) {
        int c = adj[u][i];
        if (c == p) {
            par_id = i;
            continue;
        }

        Calc_ddp(c, u);
        (ddp[u] *= (ddp[c] + 1)) %= mod;
    }

    if (par_id != -1)
        adj[u].erase(adj[u].begin() + par_id);
}

void Calc_udp(int u, int p) {
    int sz = adj[u].size();
    vector<ll> pfx(sz + 1);
    vector<ll> sfx(sz + 1);

    ll Prod = 1;

    for (int i = 0; i < sz; i++) {
        pfx[i] = Prod;
        (Prod *= (ddp[adj[u][i]] + 1)) %= mod;
    }

    Prod = 1;
    for (int i = sz - 1; i >= 0; i--) {
        sfx[i] = Prod;
        (Prod *= (ddp[adj[u][i]] + 1)) %= mod;
    }

    for (int i = 0; i < sz; i++) {
        int c = adj[u][i];
        udp[c] = (1 + udp[u] * pfx[i] % mod * sfx[i] % mod) % mod;
        Calc_udp(c, u);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> mod;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Calc_ddp(1, 0);
    udp[1] = 1;
    Calc_udp(1, 0);

    for (int i = 1; i <= n; i++) 
        cout << ddp[i] * udp[i] % mod << '\n';
}

/*
    DP up/down : 
    ddp[u] : so cach to den dinh u va mot so dinh trong cay con goc u (co the la 0)
    udp[u] : so cach to den dinh u va mot so dinh khong thuoc cay con goc u (co the la 0)

    ddp[u] = tich (1 + dp[ui]) voi moi ui la con u
    udp[u] = 1 + udp[cha u] * (tich tat ca (1 + dp[ui]) voi ui la con cha u khac u)  
    (co them + 1 la vi co cach to tat ca cac dinh phia tren u mau trang)

    ans = ddp * udp
*/