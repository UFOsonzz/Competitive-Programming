#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1000;
const ll mod = 1e9 + 7;
const ll pw[] = {17, 29};

int n, m, a[2 * MAXN + 5][2 * MAXN + 5];
ll expw[2][2 * MAXN + 5], pref[2 * MAXN + 5][2 * MAXN + 5], inv[2 * MAXN + 5][2 * MAXN + 5];

ll Exp(ll a, int b) {
    if (b == 0) return 1LL;

    ll tmp = Exp(a, b / 2);
    tmp = tmp * tmp % mod;

    if (b & 1) tmp = tmp * a % mod;
    return tmp;
}

ll Get_hash(int x1, int y1, int x2, int y2) {
    return (pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1] + 2 * mod) % mod * inv[x1 - 1][y1 - 1] % mod;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for (int i = 0; i < 2; i++) {
        expw[i][0] = 1;
        for (int j = 1; j <= 2 * MAXN; j++)
            expw[i][j] = expw[i][j - 1] * pw[i] % mod;
    }

    inv[2 * MAXN][0] = Exp(expw[0][2 * MAXN], mod - 2);
    inv[0][2 * MAXN] = Exp(expw[1][2 * MAXN], mod - 2);

    for (int i = 2 * MAXN - 1; i >= 0; i--) {
        inv[i][0] = inv[i + 1][0] * pw[0] % mod;
        inv[0][i] = inv[0][i + 1] * pw[1] % mod;
    }

    for (int i = 1; i <= 2 * MAXN; i++) 
        for (int j = 1; j <= 2 * MAXN; j++)
            inv[i][j] = inv[i][0] * inv[0][j] % mod;

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char x;
            cin >> x;
            a[i][j] = a[i + n][j] = a[i][j + m] = a[i + n][j + m] = x;
        }
    }

    for (int i = 1; i <= 2 * n; i++) {
        for (int j = 1; j <= 2 * m; j++) {
            pref[i][j] = expw[0][i] * expw[1][j] % mod * a[i][j] % mod;
            (pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + mod) %= mod;
        }
    }
        
    int curi = 1, cury = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // Find first diff
            int first_diff = 1, mid, left = 1, right = n * m;

            while (left <= right) {
                mid = (left + right) / 2;
                bool ok = false;

                if (mid % m == 0) {
                    if (Get_hash(curi, cury, curi + mid / m - 1, cury + m - 1) == 
                        Get_hash(i, j, i + mid / m - 1, j + m - 1))
                        ok = true;

                } else if (mid < m) {
                    if (Get_hash(curi, cury, curi, cury + mid - 1) == 
                        Get_hash(i, j, i, j + mid - 1))
                        ok = true;

                } else {
                    if (Get_hash(curi, cury, curi + mid / m - 1, cury + m - 1) == Get_hash(i, j, i + mid / m - 1, j + m - 1) &&
                        Get_hash(curi + mid / m, cury, curi + mid / m, cury + (mid % m) - 1) == Get_hash(i + mid / m, j, i + mid / m, j + (mid % m) - 1))
                        ok = true;

                }

                if (ok) {
                    first_diff = mid + 1;
                    left = mid + 1;
                } else right = mid - 1;
            }

            if (first_diff == n * m + 1) continue;
            else {
                // i + (first_diff - 1) / m --> row
                // j + ((first_diff - 1) % m) --> col
                first_diff--;

                if (a[i + first_diff / m][j + (first_diff % m)] < a[curi + first_diff / m][cury + (first_diff % m)])
                    curi = i, cury = j;
            }
        }
    }

    for (int i = curi; i <= curi + n - 1; i++) {
        for (int j = cury; j <= cury + m - 1; j++) {
            cout << (char)a[i][j];
        }

        cout << '\n';
    }
}
/*
    Dup bang thanh 2 x n, 2 x m, bai toan tro thanh tim hinh chu nhat con kich thuoc n, m co lexi nho nhat
    for tung hinh chu nhat, duy tri goc tren cung ben trai cua hinh chu nhat dang co lexi min, ta so sanh hinh chu nhat i, j hien tai voi hinh chu nhat do
    chat nhi phan de tim vi tri dau tien 2 hinh chu nhat khac nhau ( = vi tri cuoi cung bang nhau + 1)
    de check xem mot phan cua hinh chu nhat nay co bang mot phan cua hinh chu nhat kia khong ta su dung hash (hash 2 chieu) :
    voi moi a[i][j] ta cho ma hash cua o do thanh a[i][j] * pw[0][i] * pw[1][j] va hash cua mot hinh chu nhat la tong hash cac o trong hinh chu nhat do
    khi Get_hash thi ta dua tat ca ve o (1, 1) bang cach / (pw[0][x1 - 1] * pw[1][y1 - 1]) = * inv[x1 - 1][y1 - 1]
    --> ta co duoc o tren cung ben trai cua hinh chu nhat co lexi min.
*/