#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int k;
    string s;
    cin >> k >> s;
    int ans = 1;
    for (char c = 'a'; c <= 'z'; c++) {
        int l = 0, cur_cost = 0;
        for (int i = 0; i < s.size(); i++) {
            cur_cost += abs(s[i] - c);
            while (cur_cost > k) {
                cur_cost -= abs(s[l++] - c);
            }

            ans = max(ans, i - l + 1);
        }
    }

    cout << ans;
}