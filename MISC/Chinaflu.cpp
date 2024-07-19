#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fi first
#define se second
const int Limit = 3e5 + 5;
int n, m;
vector<int> adj[Limit];

/// preventing overlapping edges

map<pii, bool> Existed_Edges;

///  node special id used for matching adj lists

ll special_id[Limit];

// randomizer function

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/// adj id used for matching adj lists

ll adj_id[Limit];
map<ll, int> Existed_id;

// randomizer

ll randomizer() {
    return rng();
}

// mod and basic operators

const ll mod = 1e9 + 7;

ll Mod_Multiply(ll& x, ll y) {
    return x = x * y % mod;
}

ll Exponential(ll Number, ll Power) {
    if (Power == 0) return 1LL;
    ll tmp_value = Exponential(Number, Power / 2);
    tmp_value = tmp_value * tmp_value % mod;
    if (Power % 2 == 1) tmp_value = tmp_value * Number % mod;
    return tmp_value;
}

ll Mod_Divide(ll x, ll y) {
    return x = Mod_Multiply(x, Exponential(y, mod - 2));
}

int main() {
    cin >> n >> m;
    // initialize graph

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        // preventing overlapping edges

        if (u > v) swap(u, v);
        if (Existed_Edges.find(make_pair(u, v)) != Existed_Edges.end())
            continue; // if the edge already existed then continue
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // initialize special id

    for (int i = 1; i <= n; i++)
        special_id[i] = randomizer();

    // initialize adj id

    for (int i = 1; i <= n; i++) {
        adj_id[i] = 1LL;
        for (auto &c : adj[i])
            Mod_Multiply(adj_id[i], special_id[c]);
    }

    // calculating answer

    ll ans = 0;

    for (int i = 1; i <= n; i++) {
        if (Existed_id.find(adj_id[i]) != Existed_id.end())
            ans += Existed_id[adj_id[i]];
        Existed_id[adj_id[i]]++;
    }

    for (int i = 1; i <= n; i++) {
        for (auto &c: adj[i]) {
            if (Mod_Divide(adj_id[i], special_id[c]) == Mod_Divide(adj_id[c], special_id[i]))
                ans += (i < c); // i < c to prevent overlapping additions
        }
    }

    // printing answer

    cout << ans;
}
/*
--Sample Test--
Input: 
4 4
1 2
2 3
3 4
1 4
Output: 2
*/