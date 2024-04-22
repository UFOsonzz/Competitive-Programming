#include <bits/stdc++.h>
using namespace std;
const int N = 10;
const int Lim = (1<<21) + 2;
using pbi = pair<bool, int>;
#define fi first
#define se second
pbi ok[Lim];
int pos[22];
void dq(int mask) {
    if (!mask) {
        for (int i = 0; i < 21; i++) {
            cout << pos[i] << " ";
        }
        cout << '\n';
        return;
    }
    int cur = __builtin_popcount(mask)/2;
    int c = ok[mask].se;
    int tmp = mask ^ c;
    for (int i = 0; i < 21; i++)
        if ((tmp>>i)&1) pos[i] = cur;
    dq(c);
}
int main() {
    ok[0].fi = 1;
    for (int mask = 0; mask < (1<<21); mask++) {
        if (!ok[mask].fi) continue;
        int cur = __builtin_popcount(mask);
        if (cur == 0) {
            for (int i = 0; i < 21; i++) {
                ok[mask|(1<<i)].fi = 1;
                ok[mask|(1<<i)].se = mask;
            }
        } else {
            cur = (cur + 1) / 2;
            for (int i = cur + 1; i < 21; i++) {
                if (!(mask>>i&1) && !(mask>>(i-cur-1)&1)) {
                    ok[mask|(1<<i)|(1<<(i-cur-1))].fi = 1;
                    ok[mask|(1<<i)|(1<<(i-cur-1))].se = mask;
                }
            }
        }
    }
    dq((1<<21)- 1);
    
}