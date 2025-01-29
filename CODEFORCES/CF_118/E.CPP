#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;

int n, m, low[MAXN], num[MAXN], t = 1, cnt, dep[MAXN];

vector<int> adj[MAXN];
vector<pair<int, int>> path;

void dfs(int p, int u) {
    num[u] = low[u] = t++;

    for (auto v : adj[u]) {
        if (v == p) continue;
        
        if (!num[v]) {
            dep[v] = dep[u] + 1;
            dfs(u, v);

            low[u] = min(low[u], low[v]);
            if (low[v] == num[v]) cnt = 1;
            path.emplace_back(u, v);

        } else {
            low[u] = min(low[u], num[v]);
            if (dep[v] < dep[u]) 
                path.emplace_back(u, v);
        }
        
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    for (int i = 1; i <= n; i++) 
        if (!num[i]) dfs(i, i);

    if (cnt) cout << 0;
    else for (auto [u, v] : path) 
        cout << u << ' ' << v << '\n';
}

/*
    dieu kien de tplt manh la moi dinh den duoc root va root den duoc moi dinh
    dung cay dfs, ta danh dau canh trong cay khung la di xuong canh ngoai cay khung la di len
    mot dinh len duoc root khi va chi khi co mot chuoi cac canh di len lien tuc tu no len root
    xet mot canh ngoai tu u xuong v
    u xem may thang con trong v noi cao nhat la thang nao
    v xem u len duoc cao nhat la cho nao
    neu moi dinh deu den duoc root thi ok
*/