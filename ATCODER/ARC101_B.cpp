#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
const int MAXV = 1e9;


int n, a[MAXN + 5];

class Segtree {
    public : 
        int *seg, size;
        
        Segtree(int n) :
            size(4 * n + 5), seg(new int[4 * n + 5]) {}

        void Init() {
            memset(seg, 0, sizeof(int) * size);
        }

        void Update(int root, int tl, int tr, int pos) {
            if (tl == tr) {
                seg[root]++;
                return;
            }

            int tm = (tl + tr) / 2;
            if (pos <= tm) Update(2 * root, tl, tm, pos);
            else Update(2 * root + 1, tm + 1, tr, pos);

            seg[root] = seg[2 * root] + seg[2 * root + 1];
        }

        int Get(int root, int tl, int tr, int l, int r) {
            if (tl > r || tr < l) return 0;
            if (tl >= l && tr <= r) return seg[root];

            int tm = (tl + tr) / 2;

            return Get(2 * root, tl, tm, l, r) + Get(2 * root + 1, tm + 1, tr, l, r);
        }
} Tree(2 * MAXN);


bool check(int v) {
    Tree.Init();

    Tree.Update(1, 0, 2 * MAXN, 0 + MAXN);
    int Pre = 0;
    long long Num = 0;

    for (int i = 1; i <= n; i++) {
        
        Pre += (a[i] <= v ? 1 : -1);

        if (Pre - 1 >= -MAXN)
            Num += Tree.Get(1, 0, 2 * MAXN, 0, Pre - 1 + MAXN);

        Tree.Update(1, 0, 2 * MAXN, Pre + MAXN);
    }

    return Num > 1LL * n * (n + 1) / 4;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    int mid, left = 1, right = MAXV, ans = MAXV;

    while (left <= right) {
        mid = (left + right) / 2;

        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else left = mid + 1;
    }

    
    cout << ans;
}

/*
    Chat nhi phan ket qua bai toan, tim so nho nhat thoa man ham check
    ham check : kiem tra xem co ton tai nhieu hon n * (n + 1) / 4 day co trung vi <= mid hay khong, co thi tman, nguoc lai thi ko
*/