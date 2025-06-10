#include <bits/stdc++.h>

using namespace std;
using intv = pair<int, int>;

const int MAXN = 2e6;
const int MAXK = 5e5;
const int INF = 1e9;
const intv base = {INF, 0};

struct node {
    intv val, lazy;
    node() {}
    node(intv val, intv lazy) :
        val(val), lazy(lazy) {}
} seg[MAXN * 4 + 5];

void build(int root, int tl, int tr) {
    seg[root].val = seg[root].lazy = base;
    if (tl == tr) 
        return;

    int tm = (tl + tr) / 2;
    build(2 * root, tl, tm);
    build(2 * root + 1, tm + 1, tr);
}

void push_min(node& x, int val) {
    x.val.first = min(x.val.first, val);
    x.val.second = min(x.val.second, x.val.first);
    x.lazy.first = min(x.lazy.first, val);
    x.lazy.second = min(x.lazy.second, x.lazy.first);
}

void push_max(node& x, int val) {
    x.val.second = max(x.val.second, val);
    x.val.first = max(x.val.first, x.val.second);
    x.lazy.second = max(x.lazy.second, val);
    x.lazy.first = max(x.lazy.first, x.lazy.second);
}

void update(int root, int tl, int tr, int l, int r, int op, int height) {
    if (tl > r || tr < l)
        return;
    if (tl >= l && tr <= r) {
        if (op == 2) {
            push_min(seg[root], height);
        } else {
            push_max(seg[root], height);
        }

        return;
    }

    int tm = (tl + tr) / 2;
    push_min(seg[2 * root], seg[root].lazy.first);
    push_max(seg[2 * root], seg[root].lazy.second);
    push_min(seg[2 * root + 1], seg[root].lazy.first);
    push_max(seg[2 * root + 1], seg[root].lazy.second);
    seg[root].lazy = base;

    update(2 * root, tl, tm, l, r, op, height);
    update(2 * root + 1, tm + 1, tr, l, r, op, height);
}

void push_full(int root, int tl, int tr, int finalHeight[]) {
    if (tl == tr) {
        finalHeight[tl] = seg[root].val.second;
        return;
    }

    int tm = (tl + tr) / 2;
    push_min(seg[2 * root], seg[root].lazy.first);
    push_max(seg[2 * root], seg[root].lazy.second);
    push_min(seg[2 * root + 1], seg[root].lazy.first);
    push_max(seg[2 * root + 1], seg[root].lazy.second);
    seg[root].lazy = base;

    push_full(2 * root, tl, tm, finalHeight);
    push_full(2 * root + 1, tm + 1, tr, finalHeight);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]) {
    // n = 10;
    // k = 6;
    // op[0] = 1; left[0] = 1; right[0] = 8; height[0] = 4;
    // op[1] = 2; left[1] = 4; right[1] = 9; height[1] = 1;
    // op[2] = 2; left[2] = 3; right[2] = 6; height[2] = 5;
    // op[3] = 1; left[3] = 0; right[3] = 5; height[3] = 3;
    // op[4] = 1; left[4] = 2; right[4] = 2; height[4] = 5;
    // op[5] = 2; left[5] = 6; right[5] = 7; height[5] = 0;

    build(1, 0, n - 1);
    for (int i = 0; i < k; i++) {
        update(1, 0, n - 1, left[i], right[i], op[i], height[i]);
    }

    push_full(1, 0, n - 1, finalHeight);
    // for (int i = 0; i < n; i++) {
    //     cout << i << " " << finalHeight[i] << '\n';
    // }
}


int main() {
    // int n, k, op[10], left[10], right[10], height[10], finalHeight[10];
    // buildWall(n, k, op, left, right, height, finalHeight);
}