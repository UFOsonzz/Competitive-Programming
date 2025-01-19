#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e5 + 5;
const ll mod = 1e9 + 7;

int n, q, cls[1005];
string s;

void add(ll &x, ll y) {
    x += y;
    if (x >= mod) x -= mod;
}

struct Mat {
    ll a[2][2];
    Mat() { memset(a, 0, sizeof a); }

    void init(int a1, int a2, int a3, int a4) {
        a[0][0] = a1; a[0][1] = a2; 
        a[1][0] = a3; a[1][1] = a4;
    }

    Mat operator*(Mat& y) {
        Mat res;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int t = 0; t < 2; t++)
                    add(res.a[i][j], a[i][t] * y.a[t][j] % mod);

        return res;
    }
} seg[4*N], mtx[5];

void build(int root, int tl, int tr) {
    if (tl == tr) {
        seg[root] = mtx[cls[s[tl]]];
        return;
    }

    int tm = (tl + tr) / 2;
    build(2 * root, tl, tm);
    build(2 * root + 1, tm + 1, tr);
    seg[root] = seg[2 * root] * seg[2 * root + 1];
}

void update(int root, int tl, int tr, int pos, int id) {
    if (tl == tr) {
        seg[root] = mtx[id];
        return;
    }

    int tm = (tl + tr) / 2;
    if (pos <= tm) update(2 * root, tl, tm, pos, id);
    else update(2 * root + 1, tm + 1, tr, pos, id);

    seg[root] = seg[2 * root] * seg[2 * root + 1];
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    mtx[0].init(1, 0, 0, 1); mtx[1].init(0, 1, 0, 1); 
    mtx[2].init(1, 0, 1, 0); mtx[3].init(0, 1, 1, 0);
    mtx[4].init(19, 7, 6, 20);

    cls['S'] = cls['D'] = 1;
    cls['H'] = 2;
    cls['A'] = cls['E'] = cls['U'] = cls['I'] = cls['O'] = 3;
    cls['?'] = 4;

    cin >> n >> q >> s;
    s = '@' + s;

    build(1, 1, n);
    cout << seg[1].a[0][0] << '\n';

    while (q--) {
        int i;
        char c;
        cin >> i >> c;
        update(1, 1, n, i, cls[c]);
        cout << seg[1].a[0][0] << '\n';
    }
}
/*
    y tuong dp trau, dp[i][0/1] : den vi tri i, trang thai hien tai la buon/vui thi co bao nhieu cach
    toi uu dp trau bang cach coi moi chu cai la mot ma tran thoa man dp[i] x ma tran = dp[i + 1]
    => cu moi lan update chu cai thuc ra la update ma tran thu i
    => dung segment tree de tinh nhanh tich cua tat ca ma tran xong do lay dp[0] x tich moi ma tran -> kq trong log
*/