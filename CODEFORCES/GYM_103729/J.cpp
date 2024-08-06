#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
using ll = long long;
const ll mod1 = 899999994947;
const ll mod2 = 1e9 + 7;
const ll base = 53;
string s, a;
ll pw1[N], pw2[N];
int n;

ll mul1(ll x, ll y) {
    if (!x || !y) return 0;
    ll sq = sqrt(y);
    return (x * sq % mod1 * (y/sq) % mod1 + (x * (y%sq) % mod1)) % mod1;
}
ll mul2(ll x, ll y) {
    if (!x || !y) return 0;
    ll sq = sqrt(y);
    return (x * sq % mod2 * (y/sq) % mod2 + (x * (y%sq) % mod2)) % mod2;
}

struct Hash {
    ll pre1[N], pre2[N];
    void init(string s) {
        int n = s.size();
        for (int i = 1; i <= n; i++)
            pre1[i] = (mul1(pre1[i-1], base) + (s[i-1] - 'a' + 1)) % mod1,
            pre2[i] = (mul2(pre2[i-1], base) + (s[i-1] - 'a' + 1)) % mod2;
    }
    pair<ll, ll> get(int l, int r) {
        if (l > r) return {0, 0};
        return {(pre1[r] - mul1(pre1[l-1], pw1[r - l + 1]) + mod1) % mod1,(pre2[r] - mul2(pre2[l-1], pw2[r - l + 1]) + mod2) % mod2} ;
    }
};
Hash v, rv;
void solve(string s, int ty, int I, int J) {
    v.init(s);
    reverse(s.begin(), s.end());
    rv.init(s);
    int n = s.size();
    for (int i = 1; i <= n; i++) {


        if (i % 2 == 0 && v.get(1, i/2) == v.get(i/2+1, i) && v.get(i+1, n) == rv.get(1, n - i)) {
            if (!ty) assert(I+i/2 <= J), cout << I + i/2 << " " << J;
            else assert(J-i/2 >= I), cout << I << " " << J - i/2;
            exit(0);
        }
        if (i < n-i+1 && v.get(1, i) == v.get(n-i+1, n) && v.get(i+1, n-i) == rv.get(i+1, n-i)) {
            if (!ty) cout << I << " " << I+i-1;
            else cout << J-i+1 << " " << J;
            exit(0);
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i <= N-5; i++)
        pw1[i] = mul1(pw1[i-1], base),
        pw2[i] = mul2(pw2[i-1], base);
    cin >> s;
    n = s.size();
    s = " " + s;
    int i = 1, j = n;
    while (s[i] == s[j] && j > i) {
        ++i;
        --j;
    }

    if (i >= j) {return cout << 1 << " " << 1, 0;}

    for (int t = i; t <= j; t++) a += s[t];
    solve(a, 0, i, j);
    reverse(a.begin(), a.end());

    solve(a, 1, i, j);
    return cout << -1 << " " << -1, 0;
}
/*
    xau co the thanh palindrome se co 2 dang 
    {x}{palindrome}{t}{t}{x}
    {x}{t}{palindrome}{reverse_t}{x}
    (cac cau hinh nguoc lai ta lam tren xau reverse, giai quyet tuong tu)
    ** ve hinh o ca hai truong hop de biet ly do ta duoc phep loai di {x} dai nhat (neu hau to va tien to dang bang nhau thi pop het)**
*/