#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1 << 18;
const int MAXV = 60;

int n, a[MAXN + 5], dp[MAXV + 2][MAXN + 5];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    int ans = 0;

    for (int t = 1; t <= MAXV; t++) {
        for (int i = 1; i <= n; i++) {
            if (a[i] == t) dp[t][i] = i + 1;
            else dp[t][i] = dp[t - 1][dp[t - 1][i]];

            if (dp[t][i] != 0) ans = max(ans, t);
        }
    }

    cout << ans;
}
/*
    Hinh dung cac buoc gop deu duoc thuc hien theo chieu tu trai sang phai (Gop so ben trai voi so ben phai)

    vi N <= 2 ^ 18 va Ai <= 40 nen maxval <= 40 + 18 = 58
    Ta nhay log mang dp[v][i] = j + 1 co nghia la chuyen duoc toan bo doan con [i, j] thanh gia tri v
    dp[v][i] = dp[v - 1][dp[v - 1][i]] (Dung vi ta hinh dung cac buoc gop deu la theo chieu tu trai qua phai)
*/