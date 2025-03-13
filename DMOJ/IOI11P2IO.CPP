#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e5 + 5;
const int MAXK = 1e6 + 5;
const int INF = 1e9;

int n, k, depth[MAXN], ans = INF;
ll dist[MAXN];
vector<pair<int, ll>> adj[MAXN];
map<ll, int> sub_dist[MAXN];

void dfs_init(int p, int u) {
    for (auto c : adj[u]) {
        if (c.first == p)
            continue;

        dist[c.first] = dist[u] + c.second;
        depth[c.first] = depth[u] + 1;
        dfs_init(u, c.first);
    }
}

void dfs(int p, int u) {
    sub_dist[u][dist[u]] = depth[u];
    for (auto c : adj[u]) {
        if (c.first == p)
            continue;

        dfs(u, c.first);
        if (sub_dist[u].size() < sub_dist[c.first].size()) 
            swap(sub_dist[u], sub_dist[c.first]);
        
        for (auto v : sub_dist[c.first]) {
            ll search_value = k - v.first + 2 * dist[u];
            if (sub_dist[u].find(search_value) != sub_dist[u].end()) 
                ans = min(ans, sub_dist[u][search_value] + v.second - 2 * depth[u]);
        }

        for (auto v : sub_dist[c.first]) {
            if (sub_dist[u].find(v.first) == sub_dist[u].end())
                sub_dist[u][v.first] = v.second;
            else sub_dist[u][v.first] = min(sub_dist[u][v.first], v.second);
        }

        sub_dist[c.first].clear();
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;

    for (int i = 1; i < n; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        ++u; ++v;
        adj[u].emplace_back(v, l);
        adj[v].emplace_back(u, l);
    }

    dfs_init(0, 1);
    dfs(0, 1);

    if (ans == INF) 
        return cout << -1, 0;
    
    cout << ans;
}

/*
    voi moi dinh u ta xac dinh xem la duong di do dai K di qua it duong nhat o u dai bao nhieu
    co dinh dinh u va mot dinh v khac trong cay con goc u ta co dist[v] + ... - 2 * dist[u] = K
    => ... = K - dist[v] + 2 * dist[u] => neu biet u va mot dinh v ta co the biet dist[x] can tim la bao nhieu 
    (x la dinh con lai trong duong di tu x -> v)
    => gop set, voi moi dinh u ta duy tri map sub_dist[u][val] = depth[x] nho nhat thoa man dist[x] = val
    khi xet mot phan tu trong tap nho ta tim trong map to hien tai xem co ton tai dist[x] = K - dist[v] + 2 * dist[u] hay khong
    => update ket qua
*/