#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1005;
int n, q;
ll a[N][N], x, b;
int main() {
    cin >> n >> q >> x >> b;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    auto subfull = []() {
        while (q--) {
            for (int i = 1; i <= n / 2; i++) {
                for (int j = 1; j <= n; j++) {
                    if (min(j, n - j) < i) continue;
                    swap(a[i][j], a[j][n - i + 1]);
                    swap(a[n - j + 1][i], a[i][j]);
                    swap(a[n - i + 1][n - j + 1], a[n - j + 1][i]);
                }
            }
            a[n][n] = (a[n][n] + x) % b;
            int tmp = (a[n][n] * 2 % n) + 1;
            if ((a[n][n] - a[tmp][tmp]) % 2 == 0) 
                swap(a[n][n], a[tmp][tmp]);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cout << a[i][j] << " ";
            }
            cout << '\n';
        }
    };
}
