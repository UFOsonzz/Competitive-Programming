#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int a[N][N];
int n;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n / 2; i++) {
        for (int j = 1; j <= n; j++) {
            if (min(j, n - j) < i) continue;
            swap(a[i][j], a[j][n - i + 1]);
            swap(a[n - j + 1][i], a[i][j]);
            swap(a[n - i + 1][n - j + 1], a[n - j + 1][i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << '\n';
    }
}
/*
3
1 2 3
4 5 6
7 8 9
*/
