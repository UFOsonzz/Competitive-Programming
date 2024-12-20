#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;

int n, p[MAXN], cnt;
vector<int> adj[MAXN];

void dfs(int pa, int u) {
    for (auto c : adj[u]) {
        if (c == pa) continue; 
        dfs(u, c);

        // Tham lam tu la len goc
        if (p[c] == 0 && p[u] == 0) {
            p[c] = u;
            p[u] = c;
            cnt += 2;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, 1);
    for (int i = 1; i <= n; i++) {
        // Noi thang thua vao nhom cua mot trong cac thang lien ke
        if (p[i] == 0) {
            int v = adj[i][0];
            p[i] = p[v];
            p[v] = i;
            cnt += 2;
        }
    }

    cout << cnt << '\n';
    for (int i = 1; i <= n; i++) 
        cout << p[i] << " ";

}

/*
    Ghep cap tham lam tu la len goc theo nguyen ly cua bai toan maximum matching tren cay
    Voi nhung thang chua duoc ghep cap thi luon ton tai mot thang lien ke da duoc ghep
    khi ghep vao nhom cua thang do thi gia su nhom la a <-> b se tro thanh a->b->c->a => ans += 2
*/