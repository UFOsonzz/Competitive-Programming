#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 250005;
const int MAXA = 5e4 + 1;

int n, a[MAXN], q;

struct BIT {
    int LIM, *tree;

    BIT() {}
    BIT(int lim) :
        LIM(lim), tree(new int[LIM + 5]) {
            for (int i = 0; i <= lim; i++)
                tree[i] = 0;
        }

    int get(int p) {
        int idx = p, ans = 0;
        while (idx > 0) {
            ans += tree[idx];
            idx -= (idx & (-idx));
        }

        return ans;
    }

    void update(int u, int v) {
        int idx = u;
        while (idx <= LIM) {
            tree[idx] += v;
            idx += (idx & (-idx));
        }
    }

    int getRange(int l, int r) {
        if (l > r) return 0;
        return get(r) - get(l - 1);
    }
} Pfx_tree(MAXA), Sfx_tree(MAXA);

pair<int, int> Query[MAXN];
ll Query_res[MAXN];
vector<int> Container[MAXN];

int dupA[MAXN];
bool updated[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    cin >> q;

    for (int i = 1; i <= q; i++) {
        int id, x;
        cin >> id >> x;
        Query[i] = {id, x};
        Container[id].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        ll Prev = a[i];
        for (auto c : Container[i]) {
            Query_res[c] += Pfx_tree.getRange(Query[c].second + 1, Prev) - Pfx_tree.getRange(Prev + 1, Query[c].second);
            Prev = Query[c].second;
        }

        Pfx_tree.update(a[i], 1);
    }

    for (int i = n; i >= 1; i--) {
        ll Prev = a[i];
        for (auto c : Container[i]) {
            Query_res[c] += Sfx_tree.getRange(Prev, Query[c].second - 1) - Sfx_tree.getRange(Query[c].second, Prev - 1); 
            Prev = Query[c].second;
        }

        Query_res[0] += Sfx_tree.get(a[i] - 1);
        Sfx_tree.update(a[i], 1);
    }

    for (int i = 1; i <= n; i++)
        dupA[i] = a[i];

    vector<int> updatedPos(0);
    for (int i = 1; i <= q; i++) {
        Query_res[i] += Query_res[i - 1];
        for (auto c : updatedPos) {
            if (c == Query[i].first) continue;
            if (c < Query[i].first) {
                int add = (Query[i].second < a[c] ? -1 : 0) + (dupA[Query[i].first] < dupA[c] ? -1 : 0) + (Query[i].second < dupA[c] ? 1 : 0) + (dupA[Query[i].first] < a[c] ? 1 : 0);
                Query_res[i] += add;
            } else {
                int add = (Query[i].second > a[c] ? -1 : 0) + (dupA[Query[i].first] > dupA[c] ? -1 : 0) + (Query[i].second > dupA[c] ? 1 : 0) + (dupA[Query[i].first] > a[c] ? 1 : 0); 
                Query_res[i] += add;
            }
        }

        if (!updated[Query[i].first]) updatedPos.push_back(Query[i].first);
        dupA[Query[i].first] = Query[i].second;
        updated[Query[i].first] = true;
    }

    for (int i = 1; i <= q; i++)
        cout << Query_res[i] << '\n';
}

/*
    Xu ly truy van offline : 
    voi moi truy van i, ket qua
        = ket qua truy van i - 1 + (loi nhuan co duoc khi thay gia tri hien tai tu dupA[i] thanh x) 
            + phan xet rieng voi cac vi tri bi thay doi trong cac truy van truoc do

        phan xet rieng voi cac vi tri bi thay doi trong cac truy van truoc do 
            = (xoa quan he cua x voi a[i] ban dau) + (xoa quan he cua dupA o vi tri cua x voi dupA[i]) 
            + (them quan he cua x voi dupA[i]) + (them quan he cua dupA o vi tri cua x voi a[i] ban dau)
    dpt tg co q^2 nhung ko tle
*/