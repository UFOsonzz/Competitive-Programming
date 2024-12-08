#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 1e9;
const long long LINF = 1e18;

int n, a[MAXN];

bool check(int mi) {
    long long cur_sum = 0;
    long long cur_max = -LINF;

    for (int i = 1; i <= n; i++)
        a[i] -= mi;

    for (int i = 1; i <= n; i++) {
        if (cur_sum > 0) cur_sum += a[i];
        else cur_sum = a[i];

        cur_max = max(cur_max, cur_sum);
    }

    for (int i = 1; i <= n; i++)
        a[i] += mi;

    return cur_max >= 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    int mi, le = -INF, ri = INF, ans;

    while (le <= ri) {
        mi = (le + ri) / 2;
        
        if (check(mi)) {
            ans = mi;
            le = mi + 1;
        } else ri = mi - 1;
    }

    cout << ans;
}

// Chat nhi phan gia tri TBC -> dua ve bai toan tong doan con lon nhat