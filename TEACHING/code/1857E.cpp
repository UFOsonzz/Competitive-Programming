#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n;
using pii = pair<int, int>;
#define fi first
#define se second
using ll = long long;
pii a[N];
ll pre[N], ans[N];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].fi;
        a[i].se = i;
    }

    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + a[i].fi;
    for (int i = 1; i <= n; i++) 
        ans[a[i].se] = 1LL * i * a[i].fi - 2 * pre[i] + pre[n] - 1LL * (n - i) * a[i].fi + n; 
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();

}