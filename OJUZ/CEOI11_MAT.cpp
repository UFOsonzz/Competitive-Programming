#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6;

int n, m, idx[MAXN + 5], s[2 * MAXN + 5], lt[MAXN + 5], rt[MAXN + 5], pi[2 * MAXN + 5];

struct linked_list {
    int n, *l, *r;

    linked_list(int n_) :
        n(n_), l(new int[n_ + 5]), r(new int[n_ + 5]) {
            for (int i = 1; i <= n; i++) {
                l[i] = i - 1;
                r[i] = i + 1;
            }
        }

    void del(int i) {
        int l_ = l[i], r_ = r[i];
        r[l_] = r_;
        l[r_] = l_;
    }
};

bool check(int i, int j) {
    if (i == n + 1) return false;
    if (lt[i] && s[j - i + lt[i]] > s[j]) 
        return false;
    if (rt[i] && s[j + rt[i] - i] < s[j])
        return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> idx[i];
        s[idx[i]] = i;
    }
    
    s[n + 1] = 0;

    for (int i = n + 2; i <= n + 1 + m; i++)
        cin >> s[i];

    linked_list lk(n);

    for (int i = n; i >= 1; i--) {
        lt[i] = idx[lk.l[s[i]]];
        rt[i] = idx[lk.r[s[i]]];
        lk.del(s[i]);
    }

    vector<int> ans(0);
    for (int i = 2; i <= n + m + 1; i++) {
        if (i == n + 1) continue;
        int tmp = pi[i - 1];
        while (tmp > 0 && !check(tmp + 1, i))
            tmp = pi[tmp];
        if (check(tmp + 1, i)) pi[i] = tmp + 1;
        if (i > n + 1 && pi[i] == n) ans.push_back(i - 2 * n);
    }   

    cout << (int)ans.size() << '\n';
    for (auto c : ans) cout << c << " ";
}

/*
    chuyen doi xau s trong input thanh mot hoan vi voi do cao cac cot trong doan [1...n]
    ta string matching s + # + h
    xet mot tien to gom p phan tu dau tien cua xau s
    voi ki tu thu p (hay s[p]) ta tim trong tien to do : 
    ki tu s[pmin] la ki tu nho nhat > s[p]
    ki tu s[pmax] la ki tu lon nhat < s[p]
    khi xet string matching voi xau h, thi neu h[pmax cua i] < h[i] < h[pmin cua i] thi cap nhat kmp
    cminh tinh dung : vi khi xet den mot kmp[] nao do va check ki tu thu kmp[] + 1 va i 
    thi cac thang trong kmp[] deu da match het bao gom ca pmax cua i va pmin cua i
    -> so phan tu nho hon pmax cua i = so phan tu nho hon pmax trong s[]
    so phan tu lon hon pmin cua i = so phan tu lon hon pmin trong s[]
    -> vi tri cua i = vi tri cua kmp[] + 1

    *cach tim pmin va pmax, duy tri mot linked list, ban dau 1 -> 2 -> 3 -> 4 ... -> n
    sau do di tu cuoi ve dau cua xau s[] va xoa dan cac phan tu
    tai moi thoi diem thi left voi right chinh la pmax va pmin can tim
*/