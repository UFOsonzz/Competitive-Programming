#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int cnt[97][3], mod10[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string s;
    cin >> s;
    cnt[0][0] = 1;
    
    mod10[0] = 1;
    for (int i = 1; i <= N - 5; i++)
        mod10[i] = mod10[i - 1] * 10 % 97;

    int cur_mod97 = 0, cur_mod3 = 0;
    long long ans = 0;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        cur_mod97 += (s[i] - '0') * mod10[(int)s.size() - 1 - i];
        cur_mod97 %= 97;
        cur_mod3 = (cur_mod3 + (s[i] - '0')) % 3;
        ans += cnt[cur_mod97][cur_mod3];
        cnt[cur_mod97][cur_mod3]++;
    }

    cout << ans;
}