#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

#define fi first
#define se second

const int MAXN = 2e5;

int n;
pii a[MAXN + 5];
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].fi >> a[i].se;

    int cnt = 0, ans = 0;
    sort(a + 1, a + 1 + n);

    for (int i = n; i >= 1; i--) {
        pq.push(a[i].se);

        // bat buoc phai mua
        if (i - 1 + cnt < a[i].fi) {
            ans += pq.top();
            pq.pop();
            ++cnt;
        }

    }

    cout << ans;
}
/*
    Tham lam bang cach sort cac phan tu theo a[i].fi (so moi quan he), giai thich :
    Neu co duoc a[i] bang cach dat duoc a[i].fi moi quan he thi chac chan co duoc a[j (j < i)] vi a[j].fi < a[i].fi
    Ta di tu cuoi ve va tri hoan viec mua cac thang a[i] bang a[i].se tien de toi uu chi phi va chi mua khi bat buoc phai mua
    (bat buoc phai mua la khi neu khong mua o thoi diem nay thi mua tat ca cac thang o sau cung khong du)
    - Tai sao o moi vi tri ta lai chi mua nhieu nhat 1 ket noi : 
    xet vi tri i, de den duoc vi tri i (tuc la da di qua vi tri i + 1) thi (i + cnt >= a[i + 1].fi)
    gia su (i - 1 + cnt < a[i].fi <= a[i + 1].fi) thi ta cung chi can mua them nhieu nhat 1 ket noi de thoa man dieu kien
    - Tai sao sau khi duyet xong thi tat ca deu du ket noi :
    gia su sau khi duyet va mua cac ket noi xong thi ta co nguoi i la nguoi dau tien khong co du ket noi va cung khong duoc mua
    i la nguoi dau tien ko du --> co san ket noi cua i - 1 nguoi tu 1 den i - 1
    mat khac : de di qua phan tu i khi duyet thi ta phai thoa man dieu kien 
    (i - 1) + cnt >= a[i].fi va tai i thi ta chi co the tang ve trai bang cach mua cac thang a[j] (i <= j <= n) 
    noi cach khac la de di qua duoc i thi so luong thang a[j] (j >= i) da mua + (i - 1) phai >= a[i].fi --> a[i] phai du ket noi (mau thuan)
*/