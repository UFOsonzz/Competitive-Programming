#include<bits/stdc++.h>

using namespace std;
using ll = long long;

#define int long long

const int MAXN = 1e4 + 5;

int n, m, a[MAXN][20];
int ma[MAXN], dp[1 << 16], res[1 << 16], idx[MAXN];

int Find(int msk) {
    int x = msk & 1;
    msk >>= 1;
    if (x) msk |= (1 << (n - 1));
    return msk;
}

void cmax(int & a, int b) {
    a = max(a, b);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        cin >> m >> n;

        memset(dp, 0, sizeof dp);
        memset(ma, 0, sizeof ma);

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> a[i][j];
                ma[i] = max(ma[i], a[i][j]);
            }

            idx[i] = i;
        }
        
        sort(idx + 1, idx + 1 + m, [&](int a, int b) {
            return ma[a] > ma[b];
        });

        for (int e = 1; e <= min(m, n); e++) {
            int i = idx[e];
            for (int msk = 0; msk < (1 << n); msk++) {
                for (int j = 0; j < n; j++) 
                    if (msk >> j & 1 ^ 1)
                        cmax(dp[msk ^ (1 << j)], dp[msk] + a[i][j + 1]);

                res[msk] = dp[msk];
            }

            for (int msk = 0; msk < (1 << n); msk++) {
                int cur = msk;
                for (int j = 0; j < n; j++) {
                    cur = Find(cur);
                    cmax(dp[cur], res[msk]);
                }
            }
        }

        cout << dp[(1 << n) - 1] << endl;
    }
}

/*
    hinh dung giong mot bai dp bitmask thong thuong nhung van de la co the co 2 phan tu duoc chon nam cung 1 cot
    => tinh duoc dp roi thi xoay dp di, vi du nhu dung dp[01101] cap nhat cho dp[10110] 
        -> lai co van de la khong biet for thang nao truoc
    => uu tien nhung hang co max lon nhat dau tien 
    li do : neu can chon 1 phan tu thi trong cac o khoa con lai ta luon cho thang max o o khoa co max lon nhat
        => kha nang co phan tu duoc chon 
*/