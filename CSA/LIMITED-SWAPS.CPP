#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

struct node {
    int max_val, idx, num;
    node() {}
    node(int max_val_, int idx_, int num_) :
        max_val(max_val_), idx(idx_), num(num_) {}
} seg[4 * MAXN];

int n, k, a[MAXN];

node comb(node x, node y) {
    int max_val, idx, num;

    if (x.max_val == y.max_val) {
        max_val = x.max_val;
        idx = min(x.idx, y.idx);
    } else if (x.max_val > y.max_val) {
        max_val = x.max_val;
        idx = x.idx;
    } else max_val = y.max_val, idx = y.idx;

    num = x.num + y.num;
    return {max_val, idx, num};
}

void build(int root, int tl, int tr) {
    if (tl == tr) {
        seg[root] = {a[tl], tl, 1};
        return;
    }

    int tm = (tl + tr) / 2;

    build(2 * root, tl, tm);
    build(2 * root + 1, tm + 1, tr);

    seg[root] = comb(seg[2 * root], seg[2 * root + 1]);
}

void update(int root, int tl, int tr, int pos) {
    if (tl == tr) {
        seg[root].max_val = seg[root].idx = seg[root].num = 0;
        return;
    }

    int tm = (tl + tr) / 2;

    if (pos <= tm) update(2 * root, tl, tm, pos);
    else update(2 * root + 1, tm + 1, tr, pos);

    seg[root] = comb(seg[2 * root], seg[2 * root + 1]);
}

int bs(int root, int tl, int tr, int v) {
    int tm = (tl + tr) / 2;

    if (tl == tr) return tl;

    if (seg[2 * root].num >= v) 
        return bs(2 * root, tl, tm, v);

    else return bs(2 * root + 1, tm + 1, tr, v - seg[2 * root].num);
}

int get_sum(int root, int tl, int tr, int l, int r) {
    if (l > r || tl > r || tr < l) 
        return 0;
    if (tl >= l && tr <= r) 
        return seg[root].num;

    int tm = (tl + tr) / 2;

    return get_sum(2 * root, tl, tm, l, r) + 
        get_sum(2 * root + 1, tm + 1, tr, l, r);
}

pair<int, int> get_max(int root, int tl, int tr, int l, int r) {
    if (l > r || tl > r || tr < l) 
        return {0, 0};
    if (tl >= l && tr <= r) 
        return {seg[root].max_val, -seg[root].idx};

    int tm = (tl + tr) / 2;

    return max(get_max(2 * root, tl, tm, l, r),
        get_max(2 * root + 1, tm + 1, tr, l, r));
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) 
        cin >> a[i];

    build(1, 1, n);

    vector<int> swapped(0);

    for (int i = 1; i <= n; i++) {
        if (k <= 0) break;

        int pos = bs(1, 1, n, k+1);
        pair<int, int> pv = get_max(1, 1, n, 1, pos);
        pv.second *= -1;

        swapped.push_back(pv.first);
        update(1, 1, n, pv.second);

        k -= get_sum(1, 1, n, 1, pv.second);
    }

    for (auto c: swapped) 
        cout << c << " ";

    for (int i = 1; i <= n; i++) 
        if (get_sum(1, 1, n, i, i) > 0) 
            cout << a[i] << " ";
}
/*
    Tim thang tot nhat co the trong pham vi du phep swap
        neu co nhieu thang nhu the, dua thang o vi tri nho nhat len dau
        duy tri 3 yeu to trong 1 node segment tree (gtln, chi so, so luong phan tu trong node)
        * so luong phan tu trong node giup kiem soat so phan tu dung truoc (so phep swap can dung de dua mot so len dau)
        => lap di lap lai toi da n lan => dpt O(nlogn) ko phu thuoc vao k
*/