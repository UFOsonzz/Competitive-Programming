#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
using ll = long long;
const ll INF = 1e18;
int n;
ll pre[N], a[N], min_pre[N];
int main() {
    cin >> n;
    min_pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
        min_pre[i] = min(min_pre[i - 1], pre[i]);
    }

    auto subfull = []() {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int mid, left = 0, right = i - 1;
            while (left <= right) {
                mid = (left + right) / 2;
                if (pre[i] > min_pre[mid]) {
                    ans = max(ans, i - mid);
                    right = mid - 1;
                } else left = mid + 1;
            }
        }
        cout << ans;
    };
    subfull();
}