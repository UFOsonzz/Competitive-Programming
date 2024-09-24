// Dang bi TLE khong biet fix sao O(nlog^3) big constant
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

#define fi first 
#define se second 

const int MAXEVENT = 4e5;
const int MAXN = 1e5;
const int LG = 17;

int n, m, k;
vector<pii> edges;

struct DSU {
    int n, *pa;
    DSU(int n_) :
        n(n_), pa(new int[n_ + 5]) {
            iota(pa + 1, pa + 1 + n, 1);
        }

    int find_set(int u) {
        return (u == pa[u] ? u : pa[u] = find_set(pa[u]));
    }

    bool union_set(int u, int v) {
        u = find_set(u);
        v = find_set(v);

        if (u == v) return false;

        pa[v] = u;
        return true;
    }
};

struct DSU_rollback {
    int n, *pa, *sz;
    vector<tuple<int, int, int, int>> history;

    DSU_rollback() {}

    DSU_rollback(int n_) :
        n(n_), pa(new int[n_ + 5]), sz(new int[n_ + 5]) {
            for (int i = 1; i <= n; i++)
                pa[i] = i, sz[i] = 1;
        }

    void refresh() {
        for (int i = 1; i <= n; i++)
            pa[i] = i, sz[i] = 1;

        // assert(history.empty());
    }

    int find_set(int u) {
        return (u == pa[u] ? u : find_set(pa[u]));
    }

    bool union_set(int u, int v) {
        if (u == v) return false;
        u = find_set(u);
        v = find_set(v);

        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        history.emplace_back(u, v, pa[v], sz[u]);
        pa[v] = u;
        sz[u] += sz[v];
        return true;
    }

    void rollback(int steps) {
        while (steps--) {
            int u, v, opav, oszu;
            tie(u, v, opav, oszu) = history.back();
            history.pop_back();
            pa[v] = opav;
            sz[u] = oszu;
        }
    }
};

struct parallel_bs {
    int num, *ans, *l, *r;
    parallel_bs() {}

    parallel_bs(int num_) :
        num(num_), ans(new int[num_ + 5]), l(new int[num_ + 5]), r(new int[num_ + 5]) {
            for (int i = 0; i < num; i++)
                ans[i] = 0, l[i] = r[i] = -1;
        }
    
    void modify_range(int id, int nl, int nr) {
        l[id] = nl;
        r[id] = nr;
    }
};

struct EVENT_tree {
    int dur, n, edgenum, *existing;
    DSU_rollback dsu;
    vector<int> *events;
    parallel_bs pbs;
    vector<pii> *prior, *non_prior;

    EVENT_tree(int dur_, int n_, int edgenum_) :
        dur(dur_), n(n_), edgenum(edgenum_), events(new vector<int>[4 * dur_ + 5]), 
        prior(new vector<pii>[dur_ + 5]), non_prior(new vector<pii>[dur_ + 5]), existing(new int[edgenum_ + 5]) {
            dsu = DSU_rollback(n_);
            pbs = parallel_bs(edgenum_);
        }
    
    void refresh() {
        dsu.refresh();
    }

    void addlong_events(int root, int tl, int tr, int l, int r, int event) {
        if (tl > r || tr < l) return;
        if (tl >= l && tr <= r) {
            events[root].push_back(event);
            return;
        }

        int tm = (tl + tr) / 2;
        addlong_events(2 * root, tl, tm, l, r, event);
        addlong_events(2 * root + 1, tm + 1, tr, l, r, event);
    }

    void simulate(int root, int tl, int tr) {
        int union_cnt = 0;
        for (auto e : events[root]) {
            if (e > 0) {
                --e;
                // truong hop union canh
                union_cnt += dsu.union_set(edges[e].fi, edges[e].se);
            } else {
                ++e;
                // truong hop truy van
                int id = -e;
                bool rep = (dsu.find_set(edges[id].fi) != dsu.find_set(edges[id].se)); 
                // neu khac nhau nghia la no van dang la cau
                int mid = (pbs.l[id] + pbs.r[id]) / 2;

                if (rep) {
                    pbs.ans[id] = mid;
                    pbs.l[id] = mid + 1;
                } else {
                    pbs.r[id] = mid - 1;
                }
            }
        } 

        int tm = (tl + tr) / 2;
        if (tl != tr) {
            simulate(2 * root, tl, tm);
            simulate(2 * root + 1, tm + 1, tr);
        }

        // assert(union_cnt <= (int)dsu.history.size());
        dsu.rollback(union_cnt);
        events[root].clear();
    }

    bool bs() {
        refresh();
        bool stop = true;
        dur = 0;
        for (int i = 0; i < edges.size(); i++) {
            prior[i].emplace_back(0, i);
            if (pbs.l[i] != -1 && pbs.l[i] <= pbs.r[i]) {
                // van dang can bs
                stop = false;
                int mid = (pbs.l[i] + pbs.r[i]) / 2;
                non_prior[mid].emplace_back(0, i);
                dur += 2;
            } else prior[i].back().fi = 1;
        }

        if (stop) return true;

        int current_time = -1;
        for (int i = 0; i <= edgenum; i++) {
            for (auto e : prior[i]) {
                if (current_time == -1) ++current_time;
                if (e.fi == 0) existing[e.se] = current_time; 
                else addlong_events(1, 0, dur, current_time, dur, e.se + 1);
            } 

            for (auto e: non_prior[i]) {
                addlong_events(1, 0, dur, existing[e.se], current_time, e.se + 1); // xoa canh
                addlong_events(1, 0, dur, ++current_time, current_time, -(e.se + 1)); // truy van
                addlong_events(1, 0, dur, ++current_time, dur, e.se + 1); // add canh
            }

            prior[i].clear();
            non_prior[i].clear();
        }

        simulate(1, 0, dur);
        return false;
    }

};

int diff_array[2 * MAXN + 5];

void solve() {
    EVENT_tree tree(MAXEVENT, n, (int)edges.size());
    DSU dsu(n);

    for (int i = 0; i < edges.size(); i++) {
        bool uni = dsu.union_set(edges[i].fi, edges[i].se);
        if (uni) tree.pbs.modify_range(i, i, (int)edges.size() - 1);
    }

    for (int lg = 0; lg < LG; lg++) 
        if (tree.bs()) break;

    for (int i = 0; i < edges.size(); i++) {
        if (tree.pbs.l[i] != -1)
            diff_array[i]++, diff_array[tree.pbs.ans[i] + 1]--;
    }

    int cur_ans = 0;
    for (int i = 0; i < edges.size(); i++) {
        cur_ans += diff_array[i];
        if (i >= m) cout << cur_ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        edges.emplace_back(x, y);
    }

    cin >> k;

    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        edges.emplace_back(x, y);
    }

    solve();
}
/*
    Chat nhi phan song song xem thoi diem cuoi cung moi canh lam cau la thoi diem nao
    kiem tra bang dynamic connectivity
*/