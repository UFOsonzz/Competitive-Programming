#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using Point = pair<ll, ll>;
 
ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
 
void solve() {
    Point A, B;
    int k;
 
    cin >> A.first >> A.second >> B.first >> B.second >> k;
 
    ll a = A.first - B.first, b = B.second - A.second, a0 = 0, b0 = 0;
    ll g = gcd(abs(a), abs(b), a0, b0);
    if (a < 0) a0 = -a0;
    if (b < 0) b0 = -b0;
    
    a0 += B.second;
    b0 += B.first;

    int cnt = 0;
    while (cnt < k) {
        a0 += b / g;
        b0 -= a / g;
        cout << b0 << " " << a0 << '\n';
        ++cnt;
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
 
    while (t--)
        solve();
 
}

/*
    PICK'S THEOREM : 2S = 2I + B - 2
    // Lay 2S = cross(BA, BC)
    => |(ax - bx)(cy - by) + (by - ay)(cx - bx)| = B - 2 = gcd(|Ax - Bx|, |Ay - By|) = |g|
    => dang phuong trinh Ax + By = gcd(A, B) => Extended Euclid
    giai ra 1 nghiem sau do 1 thang += b/g mot thang -= a/g
*/