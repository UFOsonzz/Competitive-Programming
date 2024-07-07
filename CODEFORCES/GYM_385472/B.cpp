#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
using ll = long long;
int a, b, c, n;
struct node {
    int x, y, z;
    node() {}
    node(int x, int y, int z) :
        x(x), y(y), z(z) {}
    bool operator<(const node& other) const {
        return x > other.x;
    }
} paint[N];

ll bestl[N], bestr[N], ChooseA, ChooseC;
multiset<node> ms;
void Insert(node tmp) {
    ms.insert(tmp);
    ChooseA += tmp.y;
    if (ms.size() > a) {
        auto er = --ms.end();
        ChooseA -= er->y;
        ChooseC += er->z;
        ms.erase(er);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> a >> b >> c;
    n = a + b + c;
    for (int i = 1; i <= n; i++)
        cin >> paint[i].x;
    for (int i = 1; i <= n; i++)
        cin >> paint[i].y;
    for (int i = 1; i <= n; i++)
        cin >> paint[i].z;
    sort(paint + 1, paint + 1 + n, [&](node& a, node& b) {
        return a.x - a.y > b.x - b.y;
    });

    for (int i = 1; i <= a + c; i++) {
        Insert({paint[i].x - paint[i].z, paint[i].x, paint[i].z});
        bestl[i] = ChooseA + ChooseC;
    }

    ms.clear();
    ChooseC = ChooseA = 0;
    a = b;
    // ChooseA o duoi day duoc dung lam ChooseB, b -> a
    for (int i = n; i >= n - a - c + 1; i--) {
        Insert({paint[i].y - paint[i].z, paint[i].y, paint[i].z});
        bestr[i] = ChooseA + ChooseC;
    }
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ans = max(ans, bestl[i] + bestr[i + 1]);
    }
    cout << ans;
}
/*
y tuong duoc lay tu bai toan chi co A va B
**cach giai bai toan chi co A va B:
- sap xep cac phan tu theo a[i] - b[i] giam dan va chon cac a[i] cua A phan tu lon nhat va chon cac b[i] cua B phan tu nho nhat
=> ap dung y tuong do cho bai toan co A B C
- sap xep cac phan tu cung theo a[i] - b[i] giam dan khi do ta luon chon het cac phan tu a[i] nam ben trai roi moi chon cac phan tu B nam ben phai
-> for cac vach phan cach mot ben la chon a[i] va c[i], mot ben la chon b[i] va c[i], voi moi ben ta lai sap xep theo a[i] - c[i] / b[i] - c[i]
duy tri A / B phan tu lon nhat bang multiset / priority_queue ...
*/
