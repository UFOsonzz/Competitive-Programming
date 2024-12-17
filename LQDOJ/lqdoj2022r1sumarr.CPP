#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e5 + 5;
const ll mod = 1e9 + 7;

int n, a[MAXN];
ll pre[MAXN], sos[(1 << 19) + 2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sos[i] = a[i];
    }
    
    int msk = ((1 << __lg(n)) == n ? __lg(n) : __lg(n) + 1);

    for (int i = 0; i < msk; i++)
        for (int mask = 0; mask < 1 << msk; mask++)
            if (mask >> i & 1)
                (sos[mask] += sos[mask ^ (1 << i)]) %= mod;
    

    for (int mask = 0; mask < 1 << msk; mask++)
        sos[mask] = (sos[mask] * sos[mask]) % mod;

    for (int i = 0; i < msk; i++)
        for (int mask = (1 << msk) - 1; mask >= 0; mask--)
            if ((mask >> i) & 1)
                (sos[mask] -= sos[mask ^ (1 << i)] - mod) %= mod;
         

    ll sum = 0, tot = 0;
    for (int i = 0; i < n; i++)    
        (sum += a[i]) %= mod;

    for (int i = 0; i < n; i++)
        (tot += (a[i] * sum) % mod) %= mod;

    vector<ll> ans;
    for (int i = (1 << msk) - 1; i >= 0; i--) {
        if (i < n) 
            ans.push_back(tot);

        tot -= sos[i];
        tot %= mod;

        if (tot < 0) 
            tot += mod;
    }

    reverse(ans.begin(), ans.end());
    for (auto c: ans)
        cout << c << ' ';
}

/*
    TINH TONG AI * AJ CUA TAT CA CAC CAP I, J THOA MAN I OR J LA MASK CON CUA U
    => SAU KHI CO THI BAO HAM LOAI TRU DE TINH CHINH XAC TONG AI * AJ CUA CAC CAP I, J THOA MAN I OR J = U
    CAC TINH TONG AI * AJ CUA TAT CA CAC CAP I, J THOA MAN I OR J LA MASK CON CUA U : 
    DP SOS LUU TONG CAC THANG MASK CON CUA U -> DP SOS[U] ^ 2 = TONG TAT CA AI * AJ
*/