#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;
const int MAXN = 2e6;

ll Fac[MAXN + 5], Inv[MAXN + 5], Fib[MAXN + 5];
int x, y;

ll Exp(ll x, int y) {
    if (y == 0) return 1;
    ll Temp = Exp(x, y / 2);
    Temp = Temp * Temp % mod;
    if (y & 1) Temp = Temp * x % mod;
    return Temp;
}

ll Ckn(int k, int n) {
    if (k > n) return 0;
    return Fac[n] * Inv[k] % mod * Inv[n - k] % mod;
}

void Add(ll &x, ll y) {
    x += y;
    if (x >= mod) x -= mod;
}

int main() {
    Fac[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        Fac[i] = Fac[i - 1] * i % mod;
    Inv[MAXN] = Exp(Fac[MAXN], mod - 2);
    for (int i = MAXN - 1; i >= 0; i--)
        Inv[i] = Inv[i + 1] * (i + 1) % mod;
    Fib[1] = 1;
    for (int i = 2; i <= MAXN; i++)
        Fib[i] = (Fib[i - 1] + Fib[i - 2]) % mod;
    ll ans = 0;
    cin >> x >> y;
    for (int i = 1; i <= x; i++)
        Add(ans, Fib[i] * Ckn(x - i, y - 1 + x - i) % mod); 
        // Contribute cua Fib[i] = Fib[i] * (so duong di tu o [i, 1] -> [x, y], khong phai di tu o [i, 0] vi neu di tu [i, 0] se co the di xuong [i + 1, 0])
    for (int i = 1; i <= y; i++)
        Add(ans, Fib[i] * Ckn(y - i, x - 1 + y - i) % mod);
        // Tuong tu nhu o tren
    cout << ans;
}
/*
    Solution: Tinh contribute cua cac so o hang dau tien va cot dau tien cho ket qua o o (x, y)
    Giai thich cong thuc contribute o tren: 
    Cong thuc build bang giong voi cong thuc dp so duong di tren bang 
    --> So lan mot o (i, j) contribute cho o (x, y) bang so duong di tu no den o (x, y) nhung phai ne cac o cung hang, cung cot ra
*/