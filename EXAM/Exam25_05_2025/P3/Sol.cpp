#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 7;
const long double gau = 1e-5;

int n, m;
long double a[maxn], ap = 0, b[maxn], f[maxn], sum;

bool Check(long double k) {
    copy(a + 1, a + n + 1, b + 1);
    long double ans = b[2] - k;
    f[2] = b[2] - k;
    for (int i = 3; i < n; i++) {
        f[i] = max(b[i] - k, f[i - 1] + b[i] - k);
        ans = max(ans, f[i]);
    }

    return (sum - n * k) - ans <= 0;
}

long double bs() {
    long double l = 0;
    long double h = ap;
    while (h - l >= gau) {
        long double mid = (l + h) / 2;
        if (Check(mid)) h = mid;
        else l = mid;
    }

    return h;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ap = max(ap, a[i]);
        sum += a[i];
    }

    cout << fixed << setprecision(3);
    cout << bs();
}