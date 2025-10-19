#include<bits/stdc++.h>
using namespace std;

const int N = (int)1e5 + 5;
int t, n, cnt0, cnt[N], a[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> t;

    while (t--) {
        cin >> n;
        cnt0 = 0;

        bool ok = true;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x >> a[i];
            if (!a[i]) {
                ++cnt0;
                continue;
            }
            if (x == 1) cnt[a[i]]++;
            if (x == 2) {
                if (cnt[a[i]] > 0) cnt[a[i]]--;
                else if (cnt0 > 0) --cnt0;
                else ok = false;
            }
        }

        for (int i = 1; i <= n; i++) cnt[a[i]] = 0;
        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}
//196
