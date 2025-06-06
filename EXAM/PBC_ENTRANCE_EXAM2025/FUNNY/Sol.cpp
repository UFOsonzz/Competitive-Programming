#include <bits/stdc++.h>
using namespace std;

long long get(long long x, vector<int>& valid_ending) {
    long long ans = 0;
    for (auto c : valid_ending) {
        if (x / 100 * 100 + c > x) {
            ans += x / 100;
        } else ans += x / 100 + 1;
    }

    return ans;
}

void solve(vector<int>& valid_ending) {
    long long a, b;
    cin >> a >> b;

    cout << get(b, valid_ending) - get(a - 1, valid_ending) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t, k;
    cin >> t >> k;

    vector<int> valid_ending(0);

    for (int i = 0; i <= 99; i++) {
        if (i % k == 0)
            valid_ending.push_back(i);
    }

    while (t--) {
        solve(valid_ending);
    }

}