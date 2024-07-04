#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int n, a[N], q;
map<ll, int> mp;
void solve() {
    mp.clear();
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], mp[a[i]]++;
    cin >> q;
    while (q--) {
        ll x, y;
        cin >> x >> y;
        ll delta = x*x - 4*y;
        if (sqrt(delta) != (ll)sqrt(delta)) {
            cout << 0 << " ";
            continue;
        }
        delta = sqrt(delta);
        if ((-x + delta) % 2 != 0) {
            cout << 0 << " ";
            continue;
        }
        ll v1 = (x - delta) / 2;
        ll v2 = x - v1;

        if (v1 == v2) cout << 1LL * mp[v1] * (mp[v1] - 1) / 2 << " ";
        else cout << 1LL * mp[v1] * mp[v2] << " ";
    }
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
}