#include <bits/stdc++.h>
using namespace std;
#define print(x) cout << "[" << (x) << "]"
const int N = 1e5 + 5;
const int B = 605;
using ll = long long;
const ll mod = 1e9 + 7;
ll fac[2*N], inv[2*N];
ll Exp(ll a, ll b) {
    if (!b) return 1LL;
    ll tmp = Exp(a, b / 2);
    tmp = tmp * tmp % mod;
    if (b & 1) tmp = tmp * a % mod;
    return tmp;
}

ll Euler(int m, int n) {
    return fac[n + m - 1] * inv[n - 1] % mod * inv[m] % mod;
}

void add(ll &x, ll y) {
    x += y;
    if (x >= mod) x -= mod;
}

int n, k;
ll dp[B][N], f[2][N];
int main() {
    fac[0] = 1;
    for (int i = 1; i <= 2 * N - 5; i++)
        fac[i] = fac[i - 1] * i % mod;
    inv[2 * N - 5] = Exp(fac[2 * N - 5], mod - 2);
    for (int i = 2 * N - 6; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    cin >> n >> k;
    dp[0][0] = 1;
    f[0][0] = 1;
    for (int i = 1; i <= min(n, B - 5); i++) {
        for (int j = 1; j <= k; j++) {
            if (j >= i) add(dp[i][j], (dp[i][j - i] + dp[i - 1][j - i]) % mod);
            if (j >= n + 1) dp[i][j] = (dp[i][j] - dp[i - 1][j - n - 1] + mod) % mod;
            add(f[i & 1][j], dp[i][j]);
        }
    }
    ll ans = 0;
    for (int i = 0; i <= k; i++) {
        add(ans, Euler(k - i, n) * (f[0][i] - f[1][i] + mod) % mod);
    }
    cout << ans;
}
/*
dua bai toan ve tim so day a[] sao cho a[i] < i va tong day = k
- ta dem so day bang bao ham loai tru :
mot day khong thoa man khi ton tai a[i] >= i
nhu vay neu ta nhin duoi dang bitmask n phan tu voi phan tu i bat <=> a[i] >= i bai toan se tro ve bai dem so so nguyen to cung nhau voi x
xet day gom n phan tu a[i] = i, goi dp[i][j] la so cach de tao ra tong j tu i phan tu trong day a[], goi f[0/1][j] lan luot la so cach tao ra tong j tu chan / le phan tu trong day a[]
tu day ta co cong thuc ans = tong (chiakeo(k - x, n) * (f[0][x] - f[1][x]) voi moi 0 <= x <= k)
** cach tinh mang dp **
cong thuc : dp[i][j] = dp[i][j - i] + dp[i - 1][j - i] - dp[i - 1][j - (n + 1)];
dp[i][j - i] -> dp[i][j] la dat mot thanh nam ngang do dai i duoi i phan tu dang co
dp[i - 1][j - i] -> dp[i][j] la dat mot thanh nam ngang do dai i + 1 duoi i phan tu dang co va tao ra them phan tu thu i + 1
- dp[i - 1][j - (n + 1)] la de loai di cac trang thai ma sau khi dat cac thanh ngang thi xuat hien phan tu lon nhat = (n + 1) (cac phan tu nay bi loai vi day a[] co a[i] = i)
*/
