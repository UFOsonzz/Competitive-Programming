#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6;

int n, a[MAXN + 5];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int cur_max = a[1], max_ans = 0;
    cout << max_ans << " ";
    for (int i = 2; i <= n; i++) {
        if (a[i] <= cur_max) {
            max_ans = max(max_ans, cur_max % a[i] + a[i] % cur_max);
        } else if (a[i] > cur_max && a[i] < 2 * cur_max) {
            max_ans = max(max_ans, a[i]);
            cur_max = a[i];
        } else {
            for (int j = 1; j < i; j++) {
                max_ans = max(max_ans, a[i] % a[j] + a[j] % a[i]);
            }

            cur_max = a[i];
        }

        cout << max_ans << " ";
    }

    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) 
        solve();
}

/*
    x < y -> f(x, y) <= x + y % x <= x + y - x = y
    dau "=" xay ra <=> x < y < 2x 
    -> f(x, y) neu y < max_val thi f(x, y) <= y_max <= 2nd_max <= f(2nd_max, max_val) 
    -> toi uu nhat la luon chon y = max_val
    for tu 1 -> i, 
        neu a[i] <= cur_max, xet max_ans voi f(a[i], cur_max)
        neu cur_max < a[i] < 2 * cur_max -> max_ans = a[i]
        neu a[i] >= 2 * cur_max -> brute force, so lan brute force nhieu nhat la log lan
*/