#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e3 + 5;
const ll mod = 1e9 + 7;

int n, q;
struct Points {
    int x, y;
} a[MAXN], p;

unordered_map<double, int> mp[MAXN], tmp;
int cnt[MAXN][2][2];
int dem[2][2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> q;

    for (int i = 1; i <= n; i++) 
        cin >> a[i].x >> a[i].y;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            /// tinh vector a[i]a[j]
            int x = a[j].x - a[i].x;
            int y = a[j].y - a[i].y;

            if (x == 0) cnt[i][1][0]++;
            else if (y == 0) cnt[i][0][1]++;
            else cnt[i][0][0]++;
            if (x != 0) mp[i][(double)-y / x]++;
        }
    }

    for (int i = 1; i <= q; i++) {

        ll ans = 0;
        tmp.clear();
        dem[0][0] = dem[0][1] = dem[1][0] = dem[1][1] = 0;
        cin >> p.x >> p.y;

        for (int j = 1; j <= n; j++) {
            /// chon aj lam goc vuong
            int x = a[j].x - p.x;
            int y = a[j].y - p.y;

            if (x == 0) ans += cnt[j][0][1] + cnt[j][1][1] + dem[0][1] + dem[1][1];
            else if (y == 0) ans += cnt[j][1][0] + cnt[j][1][1] + dem[1][0] + dem[1][1];
            else {
                if (mp[j].find((double)x / y) != mp[j].end()) ans += mp[j][(double)x / y];
                if (tmp.find((double)x / y) != tmp.end()) ans += tmp[(double)x / y];
            }

            if (x == 0 && y == 0) dem[1][1]++;
            else if (x == 0) dem[1][0]++;
            else if (y == 0) dem[0][1]++;
            else dem[0][0]++;

            if (x != 0) tmp[(double) -y / x]++;
        }

        cout << ans << '\n';
    }
}

/*
    Xet 2 truong hop : 
        - 1 thang trong q thang lam goc vuong, neu no lam goc vuong thi gia su la A -> dot(AB, AC) = 0
        -> AB.x * AC.x = -AB.y * AC.y -> AB.x / AB.y = -AC.y / AC.x -> 
            for 1 vong cho q thang + for 1 vong cho n thang, voi moi cap thi dem xem co bao nhieu toa do thoa man ve trai
        - 1 thang trong q thang ko lam goc vuong
        -> for 1 vong cho q thang + for 1 vong cho n thang lam goc vuong, voi moi cap dem xem co bao nhieu thang thoa man tuong tu truong hop 1
*/
