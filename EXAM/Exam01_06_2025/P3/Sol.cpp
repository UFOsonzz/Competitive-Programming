#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> b(n), c(n);
    for (int &x : b) cin >> x;
    for (int &x : c) cin >> x;

    sort(b.begin(), b.end());
    sort(c.begin(), c.end());

    int i = 0, j = n - 1;
    long long res = LLONG_MAX;

    while (i < n && j >= 0) {
        long long sum = 1LL * b[i] + c[j];
        res = min(res, abs(sum));

        if (sum < 0) i++;
        else if (sum > 0) j--;
        else {
            res = 0;
            break;
        }
    }

    cout << res << '\n';
}
