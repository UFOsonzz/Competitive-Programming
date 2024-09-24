#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;
const int LG = 22;

int n, q, p[MAXN + 5];
vector<int> idx[MAXN + 5];

struct node {
    int val, cl, cr;
    node() : val(0) {}
    node(int val, int cl, int cr) :
        val(val), cl(cl), cr(cr) { val = 0; }    

    void show() {
        cout << val << " " << cl << " " << cr << '\n';
    }
};

struct Persistent_IT {
    int cnt, *root_id;
    node *seg;

    Persistent_IT() : 
        root_id(new int[MAXN + 5]), seg(new node[MAXN * LG]) { cnt = 0; }

    int init(int tl, int tr) {
        
        int id = ++cnt;
        int tm = (tl + tr) / 2;
        
        if (tl != tr) {
            seg[id].cl = init(tl, tm);
            seg[id].cr = init(tm + 1, tr);
        }

        return id;
    }

    int add(int root, int tl, int tr, int pos) {
        int id = ++cnt;
        int tm = (tl + tr) / 2;

        if (tl == tr) {
            seg[id].val = 1;
            return id;
        }

        int cl, cr;
        if (pos <= tm) {
            cl = add(seg[root].cl, tl, tm, pos);
            cr = seg[root].cr;
        } else {
            cl = seg[root].cl;
            cr = add(seg[root].cr, tm + 1, tr, pos);
        }

        seg[id] = {seg[cl].val + seg[cr].val, cl, cr};
        //seg[id].show();
        return id;
    }

    int get(int root, int tl, int tr, int l, int r) {
        if (tl > r || tr < l) return 0;
        if (tl >= l && tr <= r) return seg[root].val;

        int tm = (tl + tr) / 2;
        return get(seg[root].cl, tl, tm, l, r) + get(seg[root].cr, tm + 1, tr, l, r);
    }
};

int last_id[MAXN + 5];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        idx[p[i]].push_back(i);
    }

    
    Persistent_IT PIT;
    PIT.root_id[0] = PIT.init(1, n);

    int cnt = 0;

    for (int i = MAXN; i >= 1; i--) {
        for (auto x : idx[i]) 
            PIT.root_id[++cnt] = PIT.add(PIT.root_id[cnt], 1, n, x);
        
        last_id[i] = cnt;
    }
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        
        int ans = 0, mid, left = 1, right = r - l + 1;
        while (left <= right) {
            mid = (left + right) / 2;
            if (PIT.get(PIT.root_id[last_id[mid]], 1, n, l, r) >= mid) {
                ans = mid;
                left = mid + 1;
            } else right = mid - 1;
        }

        cout << ans << '\n';
    }
    
}

/*
    Chat nhi phan + persistent segment tree, add cac phan tu tu lon den be
    cu moi lan add tao ra phien ban khac cua cay -> co cac phien ban ma chi gom cac so >= mid
*/