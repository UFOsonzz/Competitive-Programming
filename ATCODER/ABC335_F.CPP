#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e5 + 2;
const int B = 450;
const int mod = 998244353;

int n, dp[MAXN], a[MAXN];
int dp1[B + 5][B + 5];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = n; i >= 1; i--) {
        dp[i] = 1;

        if (a[i] < B)
            (dp[i] += dp1[a[i]][i % a[i]]) %= mod;
        else for (int j = 1; i + j * a[i] <= n; j++)
            (dp[i] += dp[i + a[i] * j]) %= mod;

        for (int j = 1; j < B; j++)
            (dp1[j][i % j] += dp[i]) %= mod;
    }

    cout << dp[1];
}

/*
    dp chia can 2 truong hop cua ai
        truong hop 1 : ai < sqrt(n)
            => voi moi thang ai nhu vay ta them gia tri cua dp[i] vao dp1[ai][i % ai]
        truong hop con lai thi dp[i] chi co the cap nhat cho nhieu nhat sqrt(n) gia tri khac
            => duyet trau
*/