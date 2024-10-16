#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

#define fi first
#define se second

const int MAXN = 3e5;

int n, q;
long long a[MAXN + 5];
vector<pii> edges;
map<pii, int> curId;
pii exist[MAXN + 5];

struct DSU_rollback {
    int n, *pa, *sz;
    long long *wgt;
    stack<tuple<int, int, int, int, long long>> rollback_e;
    stack<pair<int, long long>> rollback_s;

    DSU_rollback() {}

    DSU_rollback(int n_, long long a[]) : 
        n(n_), pa(new int[n + 5]), sz(new int[n + 5]), wgt(new long long[n + 5]) {
            for (int i = 1; i <= n; i++) 
                pa[i] = i, sz[i] = 1, wgt[i] = a[i];
        }

    int find_set(int u) {
        return (u == pa[u] ? u : find_set(pa[u]));
    }

    bool union_set(int u, int v) {
        u = find_set(u);
        v = find_set(v);
        
        if (u == v) return false;  
        if (sz[u] < sz[v]) swap(u, v);

        rollback_e.emplace(u, v, pa[v], sz[u], wgt[u]);
        pa[v] = u;
        sz[u] += sz[v];
        wgt[u] += wgt[v];

        return true;
    }

    void upd_sum(int u, int x) {
        int pu = find_set(u);
        rollback_s.emplace(pu, wgt[pu]);
        wgt[pu] += x;
    }

    void rollback_f(int steps_e, int steps_s) {
        // Push sau thi rollback truoc
        while (steps_s--) {
            auto tp = rollback_s.top();
            wgt[tp.fi] = tp.se;
            rollback_s.pop();
        }

        while (steps_e--) {
            int u, v, oldpav, oldszu;
            long long oldwgtu;
            tie(u, v, oldpav, oldszu, oldwgtu) = rollback_e.top();
            rollback_e.pop();

            pa[v] = oldpav;
            sz[u] = oldszu;
            wgt[u] = oldwgtu;
        }
    }
};

vector<long long> Query_ans;

struct Query_Tree {
    int q;
    vector<tuple<int, int, int>> *events;
    DSU_rollback dsu;

    Query_Tree(int q_) :
        q(q_), events(new vector<tuple<int, int, int>>[4 * q + 5]) {
            dsu = DSU_rollback(n, a);
        }

    void add_events(int root, int tl, int tr, int l, int r, tuple<int, int, int> event) {
        if (tl > r || tr < l) return;
        if (tl >= l && tr <= r) {
            events[root].push_back(event);
            return;
        } 

        int tm = (tl + tr) / 2;
        add_events(2 * root, tl, tm, l, r, event);
        add_events(2 * root + 1, tm + 1, tr, l, r, event);
    }

    void re_order(int root, int tl, int tr) {
        sort(events[root].begin(), events[root].end());
        if (tl == tr) return;

        int tm = (tl + tr) / 2;
        re_order(2 * root, tl, tm);
        re_order(2 * root + 1, tm + 1, tr);
    }

    void simulate(int root, int tl, int tr) {

        int cnt_add = 0, cnt_sum = 0;
        for (auto ev : events[root]) {
            int Case, u, v;
            tie(Case, u, v) = ev;
            if (Case == 0) cnt_add += dsu.union_set(u, v);
            else if (Case == 2) {
                dsu.upd_sum(u, v);
                cnt_sum++;
            } else {
                int pu = dsu.find_set(u);
                Query_ans.push_back(dsu.wgt[pu]);
            }
        }
        
        int tm = (tl + tr) / 2;
        if (tl != tr) {
            simulate(2 * root, tl, tm);
            simulate(2 * root + 1, tm + 1, tr);
        }

        dsu.rollback_f(cnt_add, cnt_sum);
        
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    Query_Tree Event_Tree(q);

    for (int i = 1; i <= q; i++) {
        int Case;
        cin >> Case;

        if (!Case) {
            int u, v;
            cin >> u >> v;
            ++u; ++v;

            int Id = (int)edges.size();
            edges.emplace_back(u, v);
            curId[{u, v}] = Id;
            exist[Id].fi = i;
        } else if (Case == 1) {
            int u, v;
            cin >> u >> v;
            ++u; ++v;

            int Id = (curId.find({u, v}) == curId.end() ? curId[{v, u}] : curId[{u, v}]);
            exist[Id].se = i - 1;
        } else if (Case == 2) {
            int u, x;
            cin >> u >> x;
            ++u;
            // Coi thao tac add ton tai tu thoi diem i -> q
            Event_Tree.add_events(1, 1, q, i, q, {2, u, x});
        } else {
            int u;
            cin >> u;
            ++u;

            Event_Tree.add_events(1, 1, q, i, i, {3, u, 0});
        }
    }
    
    for (int i = 0; i < (int)edges.size(); i++) {
        if (exist[i].se == 0) exist[i].se = q;

        Event_Tree.add_events(1, 1, q, exist[i].fi, exist[i].se, {0, edges[i].fi, edges[i].se});
    }

    Event_Tree.re_order(1, 1, q); // Union -> Add -> Xet kq
    Event_Tree.simulate(1, 1, q);
    for (auto ans : Query_ans) 
        cout << ans << '\n';
}

/*
    Bai Dynamic Connectivity : 
    Moi canh se ton tai trong mot khoang thoi gian tu truy van l -> truy van r
    Moi canh se duoc rai ra log lan trong log doan cua segment tree
    Ta cung coi cac truy van add ton tai tu truy van i -> truy van q va cung rai ra log node
    Ta dfs tren segment tree, den mot node thi ta union cac canh -> thuc hien cac thao tac add -> xet kq (neu o node la)
    Su dung 1 stack de rollback dsu sau khi tham het cac node trong cay con cua u 
    (do phuc tap cua dsu mac dung khong co path compression, chi co union by rank / size van la O(logn) somehow :>)
*/