
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
const int INF = 1e9 + 5e8 + 1;
int n, k, l, r, p[N];
struct node {
    int idx, l, r;
    node() { idx = N-4; l = 0; r = 0; }
    node(int idx, int l, int r) :
        idx(idx), l(l), r(r) {}
} seg[23*N];
int cnt;
int build(int tl, int tr) {
    int tmp = ++cnt;
    if (tl == tr) {
        seg[tmp] = {tl, 0, 0};
        return tmp;
    }

    int tm = (tl + tr) / 2;
    int ul = build(tl, tm);
    int ur = build(tm+1, tr);
    seg[tmp] = {p[seg[ul].idx] < p[seg[ur].idx] ? seg[ul].idx : seg[ur].idx, ul, ur};
    return tmp;
}

int update(int u, int tl, int tr, int pos, int v) {
    int tmp = ++cnt;
    if (tl == tr) {
        seg[tmp] = {v, 0, 0};
        return tmp;
    }
    int tm = (tl + tr) / 2;
    int ul, ur;
    if (pos <= tm) {
        ul = update(seg[u].l, tl, tm, pos, v);
        ur = seg[u].r;
    } else {
        ul = seg[u].l;
        ur = update(seg[u].r, tm+1, tr, pos, v);
    }
    seg[tmp] = {p[seg[ul].idx] < p[seg[ur].idx] ? seg[ul].idx : seg[ur].idx, ul, ur};
    return tmp;
}

int get(int u, int tl, int tr, int l, int r) {
    if (tl > r || tr < l) return N-4;
    if (tl >= l && tr <= r) return seg[u].idx;
    int tm = (tl + tr) / 2;
    int ul = get(seg[u].l, tl, tm, l, r);
    int ur = get(seg[u].r, tm+1, tr, l, r);
    return (p[ul] < p[ur] ? ul : ur);
}

int root[N];
using T = tuple<int, int, int>;
priority_queue<T> pq;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k >> l >> r;
    p[N-4] = INF;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        p[i] += p[i-1];
    }

    root[0] = build(0, n);

    for (int i = l; i <= n; i++) {
        root[i] = root[0];
        int pos = get(root[i], 0, n, i <= r ? 0 : i - r, i - l);
        pq.emplace(p[i] - p[pos], i, pos);
        //cout << i << " " << pos << " " << p[i] - p[pos] << '\n';
    }
    long long ans = 0;
    while (k--) {
        int v, u, pos;
        tie(v, u, pos) = pq.top();
        pq.pop();
        ans += v;
        root[u] = update(root[u], 0, n, pos, N-4);
        pos = get(root[u], 0, n, u <= r ? 0 : u - r, u - l);
        pq.emplace(p[u] - p[pos], u, pos);
    }
    cout << ans;
}
/*
su dung ky thuat fracturing search: https://usaco.guide/adv/fracturing-search?lang=cpp
persistent segment tree de lay cac tien to nho nhat chua bi chon de ghep voi tien to tai i ( i la dau ben phai ) voi moi i
*/
