#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int N = 2e6 + 5;
ll fac[N], inv[N];
ll Exp(ll a, int b) {
    if (!b) return 1;
    ll tmp = Exp(a, b/2);
    tmp = tmp * tmp % mod;
    if (b&1) tmp = tmp * a % mod;
    return tmp;
}
ll Ckn(int k, int n) {
    if (k > n) return 0;
    return fac[n] * inv[k] % mod * inv[n - k] % mod;
}
int l, n;
void solve() {
    cin >> l >> n;
    ll ans = 0;
    for (int i = 0; i <= l - 2 * n; i+=2) {
        int emp = l - 2 * n - i;
        (ans += Ckn(n - 1, n + i/2 - 1) * Ckn(n, n + emp)) %= mod;
    }
    ans = (Ckn(2 * n, l) - ans + mod) % mod;
    cout << 2LL * ans % mod << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    fac[0] = 1;
    for (int i = 1; i <= N-5; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    inv[N-5] = Exp(fac[N-5], mod - 2);
    for (int i = N-6; i >= 0; i--) {
        inv[i] = inv[i+1] * (i + 1) % mod;
    }
    int t;
    cin >> t;
    while (t--) solve();

}