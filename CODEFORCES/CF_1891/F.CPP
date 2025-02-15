#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;

int n, in[MAXN], out[MAXN];
vector<int> adj[MAXN];
vector<tuple<int, int, int>> queries;

struct BIT {
    long long *tree;
    int n;
    BIT(int sz) :
        n(sz), tree(new long long[sz + 2]) {
            memset(tree, 0, sizeof(long long) * (n + 2));
        }

    void update(int pos, long long v) {
        while (pos <= n) {
            tree[pos] += v;
            pos += (pos & (-pos));
        }
    }

    long long get_prefix(int pos) {
        long long sum = 0;
        while (pos > 0) {
            sum += tree[pos];
            pos -= (pos & (-pos));
        }

        return sum;
    }

    void update_range(int l, int r, long long v) {
        update(l, v);
        update(r + 1, -v);
    }
};

void dfs(int u) {
    in[u] = ++in[0];
    for (auto c : adj[u]) 
        dfs(c);
    out[u] = in[0];
}

void solve() {
    int q;
    cin >> q;

    n = 1;
    
    for (int i = 1; i <= q; i++) {
        int ti, vi, xi;
        cin >> ti;
        if (ti == 1) {
            cin >> vi;
            adj[vi].push_back(++n);
            vi = n;
        } else cin >> vi >> xi;

        queries.emplace_back(ti, vi, xi);

    }

    BIT tree(n);
    in[0] = 0;
    dfs(1);

    for (int i = 1; i <= q; i++) {
        int ti, vi, xi;
        tie(ti, vi, xi) = queries[i - 1];
        if (ti == 1) 
            tree.update_range(in[vi], in[vi], -tree.get_prefix(in[vi]));
        else tree.update_range(in[vi], out[vi], xi);
    }

    for (int i = 1; i <= n; i++) 
        cout << tree.get_prefix(in[i]) << " ";
    cout << '\n';

    queries.clear();
    for (int i = 1; i <= n; i++)
        adj[i].clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;

    while (t--)
        solve();

}

/*
    duyet qua tat ca truy van 1 lan de biet cay cuoi cung trong ntn
    dung euler tour cua cay do, voi moi truy van update subtree thi cap nhat tu in[u] den out[u]
    khi them mot dinh moi vao thi xem hien tai no dang co gia tri la bao nhieu de tru di
*/