#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int Limit = 2e5 + 5;

int Test_num, n, a[Limit], b[Limit], Appearances[Limit];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    ll ans = 0;
    // Brute force by 2 steps
    int Brute_steps = 2;
    while (Brute_steps--) {
        for (int i = 1; i <= n; i++)
            ans += a[i];
        int current_MAD = 0;
        for (int i = 1; i <= n; i++) {
            Appearances[a[i]]++;
            if (Appearances[a[i]] >= 2 && a[i] > current_MAD) 
                current_MAD = a[i];
            b[i] = current_MAD;
        }
        // clear Appearances array
        for (int i = 1; i <= n; i++) {
            Appearances[a[i]]--;
            a[i] = b[i];
        }
    }
    // calculating after pruning block < 2
    a[n + 1] = -1; // assign value outside the range of a[i] to a[n + 1]
    int current_value = 0, current_blocksize = 0;
    for (int i = 1; i <= n + 1; i++) {
        if (a[i] != current_value) {
            ans += 1LL * (n + 1 - i) * current_value * current_blocksize + 
                   1LL * (current_blocksize + 1) * current_blocksize / 2 * current_value;
            current_blocksize = 0;
        } 
        current_blocksize++;
        current_value = a[i];
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> Test_num;
    while (Test_num--) 
        solve();

}