#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n;
using ll = long long;
ll a[N], b[N];
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i < n; i++) {
        a[i + 1] += a[i] / 2;
        a[i] &= 1;
        b[i + 1] += b[i] / 2;
        b[i] &= 1;
    }
    for (int i = n; i >= 1; i--) {
        if (a[i] < b[i]) return cout << "NO\n", void();
        if (a[i] > b[i]) return cout << "YES\n", void();
    }
    cout << "YES\n";
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
}
