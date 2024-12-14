#include <bits/stdc++.h>

using namespace std;


const int N = 1e5 + 5;
int low[N], num[N], tim, ncc, val[N], typ[N], n, m, dep[N];
vector<int> adj[N];
set<int> g2[N];
stack<int> st;
vector<pair<int, int>> ed;

void dfs(int u, int p) {
    low[u] = num[u] = ++tim;
    st.push(u);

    for (auto x : adj[u]) {
        if (x == p) {
            p = -1;
            continue;
        }
        if (num[x]) {
            low[u] = min(low[u], num[x]);
        } else {
            dfs(x, u);
            low[u] = min(low[u], low[x]);
        }
    }

    if (num[u] == low[u]) {
        ncc++;
        int s = -1;
        while (s != u) {
            s = st.top();
            st.pop();
            typ[s] = ncc;
            low[s] = num[s] = n + 1;
        }
    }

}

void getdep(int u, int p) {
    for (auto x : g2[u]) {
        if (x == p) continue;
        dep[x] = dep[u] + 1;
        getdep(x, u);
        val[u] += val[x];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        ed.emplace_back(u, v);
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!num[i]) dfs(i, 0);
        for (auto x : adj[i]) {
            if (typ[x] != typ[i]) {
                g2[typ[x]].insert(typ[i]);
                g2[typ[i]].insert(typ[x]);
            }
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        val[typ[a]]++;
        val[typ[b]]--;
    }

    for (int i = 1; i <= ncc; i++) {
        if (!dep[i]) {
            dep[i] = 1;
            getdep(i, 0);
        }
    }

    for (auto x : ed) {
        int a = typ[x.first], b = typ[x.second];
        if (a == b) {
            cout << "B";
            continue;
        }

        if (dep[a] > dep[b]) {
            if (val[a] == 0) cout << 'B';
            if (val[a] > 0) cout << 'R';
            if (val[a] < 0) cout << 'L';
        }

        if (dep[a] < dep[b]) {
            if (val[b] == 0) cout << 'B';
            if (val[b] > 0) cout << 'L';
            if (val[b] < 0) cout << 'R';
        }
    }
}

/*
    dung cay dfs : 
        - cach canh thua luon co the bi thay the duong di => neu co the la L thi cung co the la R => luon la B
        -> dua ve bai toan danh huong canh tren cay
        quy uoc canh di len la L, canh xuong duoi la R (cout doi lai thu tu tuy thu tu cin)
        neu a -> b thi cac canh tren duong di tu a -> lca(a, b) luon phai la L, cac canh tu lca(a, b) -> b luon phai la R
        -> cap nhat duong di tren cay, tuy nhien khong can dung hld vi khong phai tra loi truy van lien tuc : 
        cach cap nhat : cap nhat tai dinh a gia tri += 1, cap nhat tai dinh b gia tri -= 1
        => canh i noi tu dinh x len cha x se co trong so la tong cac dinh trong subtree x
        canh nao duong -> L
        canh nao am -> R
        canh = 0 -> B
*/
