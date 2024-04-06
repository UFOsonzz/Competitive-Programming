#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, a[N*N];
void solve() {
    cin >> n;
    for (int i = 1; i <= n*(n-1)/2; i++) 
        cin >> a[i];
    sort(a + 1, a + 1 + n*(n-1)/2);
    int j = 1;
    for (int i = n - 1; i > 0; i--) {
        cout << a[j] << " ";
        j += i;
    }
    
    cout << 1000000000 << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();

}