#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<char>> a;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;

    a.resize(n + 2, vector<char> (m + 2));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    int ans = n + m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int ii = 0; ii <= 26; ii++) 
                for (int jj = 0; jj <= 26 - ii; jj++) {
                    if (ii == jj && jj == 0) continue;
                    if (i > ii && j + jj <= m && a[i][j] == a[i - ii][j + jj])
                        ans = min(ans, ii + jj);
                    if (i + ii <= n && j + jj <= m && a[i][j] == a[i + ii][j + jj])
                        ans = min(ans, ii + jj);
                }

    cout << ans;
}

// Dirichle