#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Interval = pair<int, bool>;
#define fi first
#define se second
const int Limit = 3000;
const ll mod = 1e9 + 7;
int n, s[Limit + 5], t[Limit + 5];
vector<Interval> vecInterval;
ll dp[2 * Limit + 5][Limit + 5][2];
// dua ve bai toan day dem so cach tao ra day ngoac dung co nhieu ngoac nhat
// dp[den phan tu i][so con bo dang cho duoc bo vao chuong][da skip con bo nao chua]
// neu da skip mot con bo thi khong duoc skip mot chuong nao sau do vi nhu the thi cach ghep se khong toi uu
void Update(ll& x, ll y) {
    x += y;
    if (x >= mod) x -= mod;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        vecInterval.emplace_back(s[i], false);
    }
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        vecInterval.emplace_back(t[i], true);
    }

    sort(vecInterval.begin(), vecInterval.end());
    dp[0][0][0] = 1;
    for (int i = 0; i < 2 * n; i++) {
        for (int Cowinqueue = 0; Cowinqueue <= n; Cowinqueue++) {
            for (bool Skipped : {false, true}) {
                auto& Obj = vecInterval[i];
                if (Obj.se == false) {
                    // neu la bo
                    // chon con bo
                    Update(dp[i + 1][Cowinqueue + 1][Skipped], dp[i][Cowinqueue][Skipped]);
                    // skip con bo
                    Update(dp[i + 1][Cowinqueue][1], dp[i][Cowinqueue][Skipped]);
                } else {
                    // neu la chuong
                    // neu cho bo vao chuong
                    if (Cowinqueue > 0) Update(dp[i + 1][Cowinqueue - 1][Skipped], (ll)Cowinqueue * dp[i][Cowinqueue][Skipped] % mod);
                    // neu skip chuong (Skipped phai = false)
                    if (Skipped == false) Update(dp[i + 1][Cowinqueue][Skipped], dp[i][Cowinqueue][Skipped]);
                }
            }
        }
    }
    cout << (dp[2 * n][0][0] + dp[2 * n][0][1]) % mod;
}