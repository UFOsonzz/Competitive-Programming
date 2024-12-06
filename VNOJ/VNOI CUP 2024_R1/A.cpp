#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int n, a[N];
ll cnt1, cnt2;
void solve() {
    cnt1 = cnt2 = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 1) cnt1++;
        else if (a[i] == 2) cnt2++;
        else cnt1 += (a[i] - 2), cnt2++;
    }

    cout << cnt1 / 2 + cnt2 / 2 << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
}
