
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;
using pii = pair<ll, int>;
#define fi first
#define se second
const int Bit = 63;
ll a, b, c, d;
#define print(x) cout<<"["<<(x)<<"]"

vector<pii> Init(ll a, ll b) {
    vector<pii> Res;
    ll Chung = 0;
    int i = Bit - 1;
    for (i = Bit - 1; i >= 0; i--) {
        ll v = (a>>i&1LL);
        if (v == (b>>i&1LL)) Chung += (v << i);
        else break;
    }
    //if (!a) print(i) << '\n';
    //print(i) << '\n';
    ll org = Chung;
    for (int j = i - 1; j >= 0; j--) {
        //print("ok");
        ll v = (a>>j&1LL);
        if (!v) Res.emplace_back((Chung + (1LL << j)) >> j, j);
        else Chung += (1LL << j);
    }
    //print(Chung) << '\n';

    //cout << '\n';
    Res.emplace_back(Chung, 0);
    //if (!a) for (auto c: Res) print(c.fi), print(c.se) << '\n';
    if (i != -1) Chung = org + ((b>>i&1LL) << i);

    for (int j = i - 1; j >= 0; j--) {
        ll v = (b>>j&1LL);
        if (v) Res.emplace_back(Chung >> j, j), Chung += (1LL << j);
    }
    Res.emplace_back(Chung, 0);
    sort(Res.begin(), Res.end());
    Res.erase(unique(Res.begin(), Res.end()), Res.end());
    return Res;
}
pii Xor(pii x, pii y) {
    if (x.se > y.se) swap(x, y);
    return {(x.fi >> (y.se - x.se)) ^ y.fi, y.se};
}
bool Trung(pii x, pii y) {
    if (x.se < y.se) swap(x, y);
    return ((y.fi >> (x.se - y.se)) == x.fi);
}
void solve() {
    cin >> a >> b >> c >> d;
    vector<pii> L = Init(a, b);
    //for (auto p: L) print(p.fi), print(p.se) << '\n';
    vector<pii> R = Init(c, d);
    //for (auto p: R) print(p.fi), print(p.se) << '\n';
    vector<pii> Total;
    for (auto p: L)
    for (auto q: R)
    Total.push_back(Xor(p, q));

    vector<pii> tmp = Total;
    Total.clear();

    sort(tmp.begin(), tmp.end(), [&](pii x, pii y) {
         if ((x.fi << x.se) == (y.fi << y.se)) {
            return x.se > y.se;
         }
         return ((x.fi << x.se) < (y.fi << y.se));
    });
    for (int i = 0; i < tmp.size(); i++) {
        Total.push_back(tmp[i]);
        int j = i;
        for (j = i + 1; j < tmp.size(); j++) {
            if (!Trung(tmp[i], tmp[j])) {
                i = j - 1;
                break;
            }

            if (j == tmp.size() - 1) i = tmp.size() - 1;
        }
    }

    ll num = 0;
    for (auto p: Total)
    num += (1LL << p.se);
    num = (num + 1) / 2;
    ll cur = 0;
    for (auto p: Total) {
        ll v = (1LL << p.se);
        if (cur < num && cur + v >= num) {
            ll ans = (p.fi << p.se);
            ans += num - cur - 1;
            return cout << ans << '\n', void();
        }
        cur += v;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("medxor.inp", "r", stdin);
    //freopen("medxor.out", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
}
/*
[12][3]
[13][3]
[7][4]
[1][7]
[1][8]
[2][8]
[6][7]
[14][6]
[30][5]
[124][3]
[125][3]
*/
