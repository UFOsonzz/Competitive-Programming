#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;

int n, a[MAXN + 5], cnt0[MAXN + 5];
long long cnt1[MAXN + 5];
long long ans = 0;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("Basohang.inp", "r", stdin);
    freopen("Basohang.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j == 0) {
                if (j == a[i] / j) {
                    ans += cnt1[j];
                    cnt1[a[i]] += cnt0[j];
                    
                } else {
                    ans += cnt1[j] + cnt1[a[i] / j];
                    cnt1[a[i]] += cnt0[j] + cnt0[a[i] / j];
                }
            }
        }
 
        cnt0[a[i]]++;
    }

    cout << ans;
}