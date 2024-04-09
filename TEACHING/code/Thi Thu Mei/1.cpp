#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll a, b, c;
int main() {
    cin >> a >> b >> c;
    auto sub1 = []() {
        int ans = 5001;
        for (int i = 0; i <= c; i++) {
            for (int j = 0; j <= c; j++) {
                if (a * i + b * j == c)
                ans = min(ans, i + j);
            }
        }
        cout << ans;
    };
    auto sub2 = []() {
        ll ans = 1e5 + 1;
        for (int i = 0; i <= c; i++) {
            if ((c - a * i) % b != 0 || c < a * i) continue;
            ans = min(ans, i + (c - a * i) / b);
        }
        cout << ans;
    };
    auto sub3 = []() {
        ll ans = 1e18 + 1;
        for (int i = 0; i <= b; i++) {
            if ((c - a * i) % b != 0 || c < a * i) continue;
            ans = min(ans, i + (c - a * i) / b);
        }
        swap(a, b);
        for (int i = 0; i <= b; i++) {
            if ((c - a * i) % b != 0 || c < a * i) continue;
            ans = min(ans, i + (c - a * i) / b);
        }
        cout << ans;
    };
}