#include <bits/stdc++.h>
using namespace std;
using ld = long long;
using pld = pair<ld, ld>;
#define fi first
#define se second
const ld INF = 3e18;
const int N = 5e5 + 5;
int n;
ld a[N], b[N];
pld x[N];

ld MIN_ANS = INF;
ld sq(ld x) {
    x = abs(x);
    if (!x) return 0;
    if (x > INF / x) return INF;
    return x * x;
}
void mini(pld x, pld y) {
    ld tmp = sq(x.fi - y.fi) + sq(x.se - y.se);
    MIN_ANS = min(MIN_ANS, tmp);
}

vector<pld> tmp;
void solve(int l, int r) {
    if (r - l <= 5) {
        sort(x + l, x + r + 1, [&](pld u, pld v) {
            if (u.se == v.se) return u.fi < v.fi;
            return u.se < v.se;
        });
        for (int i = l; i <= r; i++) {
            for (int j = i + 1; j <= r; j++) {
                mini(x[i], x[j]);
            }
        }
        return;
    }

    int tm = (l + r) / 2;
    ld xm = x[tm].fi;
    solve(l, tm);
    solve(tm + 1, r);
    tmp.clear();
    int j = tm + 1;
    for (int i = l; i <= tm; i++) {
        while (j <= r && x[j].se < x[i].se) tmp.push_back(x[j++]);
        tmp.push_back(x[i]);
    }

    for (int i = j; i <= r; i++) tmp.push_back(x[i]);
    for (int i = l; i <= r; i++) x[i] = tmp[i - l];
    tmp.clear();
    for (int i = l; i <= r; i++) {
        if (sq(xm - x[i].fi) <= MIN_ANS) tmp.push_back(x[i]);
    }

    for (int i = 0; i < tmp.size(); i++) {
        for (int j = i + 1; j < tmp.size() && sq(tmp[j].se - tmp[i].se) < MIN_ANS; j++) {
            mini(tmp[i], tmp[j]);
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        x[i] = {x[i - 1].fi + a[i], x[i - 1].se + b[i]};
    sort(x, x + 1 + n);
    solve(0, n);
    cout << MIN_ANS;
}