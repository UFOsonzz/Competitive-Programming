#include <bits/stdc++.h>
using namespace std;
const int Limit = 1e5;
string s, t;
vector<int> ZConcat, tKMP, leZPrefix(Limit + 1);
void Z_function(string& str, vector<int>& Z) {
    int sz = str.size();
    Z.resize(sz + 1);
    Z[0] = 0;
    for (int i = 1, l = 0, r = 0; i < sz; i++) {
        if (i < r) {
            Z[i] = min(r - i, Z[i - l]);
        }
        while (i + Z[i] < sz && str[Z[i]] == str[i + Z[i]]) 
            Z[i]++;
        if (i + Z[i] > r) {
            l = i;
            r = i + Z[i];
        }
        // nua khoang [l, r) la substring xa nhat match voi mot tien to biet duoc sau khi xet Z[i] (r co the > i)
    }
}

void KMP(string &str, vector<int>& KMP) {
    int sz = str.size();
    KMP.resize(sz + 1);
    KMP[0] = 0;
    for (int i = 1; i < sz; i++) {
        int val = KMP[i - 1];
        while (str[val] != str[i] && val > 0)
            val = KMP[val - 1];
        if (str[val] == str[i])
            val++;
        KMP[i] = val;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> s >> t;
    string Concat = t + s;
    Z_function(Concat, ZConcat);
    KMP(t, tKMP);
    long long ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (i + 1 < (int)s.size())
            leZPrefix[min((int)t.size(), ZConcat[(i + 1) + (int)t.size()])]++;
        else leZPrefix[0]++;
    }
    for (int i = 1; i < t.size(); i++)
        leZPrefix[i] += leZPrefix[i - 1];
    for (int i = 0; i < t.size(); i++) {
        if (tKMP[i] == 0) ans += (int)s.size();
        else ans += leZPrefix[i - tKMP[i]];
    }
    cout << ans;
}

/*
Loi Giai: 
- Ta xet viec dat mot tien to cua s o phia truoc tien to cua t.
- Gia su co nhieu cac dat cung tao thanh mot xau thi ta se chi tinh cach ma tien to cua s la dai nhat
- Ve hinh cho truong hop 2 cach ghep cung tao ra mot xau: 
    + Cach ghep co tien to cua s ngan hon : 
        s : "{l}"
        t : "{k}{j}"
    + Cach ghep co tien to cua s dai hon : 
        s : "{l}{k}"
        t : "{j}"
        {j} la mot hau to trung voi tien to --> kmp somehow,
            tam ky hieu kmp[i] la mang kmp voi xau t
        {k} tren s trung voi tien to cua t --> ghep 2 xau lai roi Z somehow,
            tam ky hieu Z[i] la xau con dai nhat bat dau tu i cua s va trung voi mot tien to cua t
            (co the Z voi xau Concat = t + s)
    Ta nhan thay moi cap cach ghep cho ra cung mot xau deu co dang nay
-> co nhan xet : neu ta ghep s[0:i] voi t[0:j] va Z[i + 1] >= (j + 1) - kmp[j]  (j + 1 la do dai cua t[0:j])
    thi chac chan cach ghep nay khong phai la cach ghep co tien to cua s dai nhat vi ta co the thay the bang cach ghep
    s[0: i + (j + 1 - kmp[j])] va t[0: kmp[j] - 1] (ve hinh ra thi no giong nhu la dua {k} tu t len s va co the dua duoc boi Z[i + 1] >= len_t - kmp)
    + cung tu nhan xet tren thi ta thay duoc luon la neu Z[i + 1] < (j + 1) - kmp[j] hay Z[i + 1] <= j - kmp[j] 
        thi no chac chan la cach tao ra xau ma co tien to s lon nhat, vi neu ton tai mot cach lon hon thi Z[i + 1] trong truong hop do phai lon hon hien tai (nhin vao hinh minh hoa o tren)
-> voi moi t[0:j] thi ta chi xet ket qua voi cac tien to cua s co Z[i + 1] <= j - kmp[j]
-> ta duyet cac vi tri j va xet cac cach tao xau bang tien to t[0:j] va cac tien to cua s, ta tao mot mang cnt voi cnt[i] la so luong tien to s[0:x] co Z[x + 1] <= i
va tai j thi ans += size(s) neu kmp[j] = 0 va ans += cnt[j - kmp[j]] voi kmp[j] != 0.
*/