#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

long long x[N], w[N], sw[N], sxw[N];

void solve() {
    int n; 
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> w[i];
        sw[i] = sw[i - 1] + w[i];
        sxw[i] = sxw[i - 1] + x[i] * w[i];
    }

    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;

        assert(l <= r);
        r--;

        cout << x[r + 1] * (sw[r] - sw[l - 1]) - (sxw[r] - sxw[l - 1]) << '\n';
    }
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    solve();
}
