#include <bits/stdc++.h>
using namespace std;
const int N = 55;
int n, a[N];
void solve() {
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++)
        cin >> a[i], sum += a[i];
    if (sum % 2 == 0) return cout << "YES\n", void();
    else return cout << "NO\n", void();
}
int main() {
    int t;
    cin >> t;
    while (t--) solve();

}