#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll Rand(ll l, ll r) {
    return l + rng() % (r - l + 1);
}

int n, q;
ll w;

int main() {
    n = 8;
    q = 1;
    w = 10;

    cout << n << " " << q << " " << w << '\n';
    for (int i = 1; i < n; i++) {
        cout << i + 1 << " " << Rand(1, i) << " " << Rand(0, w) << '\n';
    }

    cout << Rand(0, n - 2) << " " << Rand(0, w - 1);
}