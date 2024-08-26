#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
const ll mod = 1e9 + 7;
int n, a[N];
ll pre[N], sos[(1 << 19) + 2];
void sub1(){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if ((i | j) >= n) continue;
            else{
                int z = i | j;
                pre[z] += 1LL * a[i] * a[j];
            }
    ll sum = 0;
    for (int i = 0; i < n; i++)
        (sum += pre[i]) %= mod, cout << sum << " ";
}
void sub2(){
    for (int i = 0; i < n; i++)
        sos[i] = a[i];
    int msk;
    for (int i = 0; i <= 20; i++){
        if ((1 << i) >= n){
            msk = i; break;
        }
    }
    for (int i = 0; i < msk; i++)
    for (int mask = 0; mask < (1 << msk); mask++){
        if ((mask >> i) & 1)
            (sos[mask] += sos[mask ^ (1 << i)]) %= mod;
    }
    for (int mask = 0; mask < (1 << msk); mask++)
        sos[mask] = (sos[mask] * sos[mask]) % mod;
    for (int i = 0; i < msk; i++)
    for (int mask = (1 << msk) - 1; mask >= 0; mask--){
        if ((mask >> i) & 1){
            sos[mask] -= sos[mask ^ (1 << i)];
            sos[mask] %= mod;
            if (sos[mask] < 0) sos[mask] += mod;
        }
    }
    ll sum = 0, tot = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    sum %= mod;
    for (int i = 0; i < n; i++)
        (tot += (a[i] * sum) % mod) %= mod;

    vector<ll> ans;
    for (int i = (1 << msk) - 1; i >= 0; i--){
        if (i < n) ans.push_back(tot);
        tot -= sos[i];
        tot %= mod;
        if (tot < 0) tot += mod;
    }
    reverse(ans.begin(), ans.end());
    for (auto c: ans) cout << c << ' ';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    if (n <= 500) sub1();
    else sub2();
}