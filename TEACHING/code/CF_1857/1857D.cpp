#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, a[N], b[N];
void solve() {
    cin >> n;
    int mn = 2e9;
    for (int i = 1; i <= n; i++) 
        cin >> a[i];
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        mn = min(mn, b[i] - a[i]);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (b[i] - a[i] == mn) ans++;
    }
    cout << ans << '\n';
    for (int i = 1; i <= n; i++) 
        if (b[i] - a[i] == mn) cout << i << " ";
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();

}