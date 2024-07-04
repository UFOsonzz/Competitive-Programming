#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int t, n, p[N], q[N];
vector<int> pos_parity[2];
void solve() {
    cin >> n;
    int pos1;
    for (int i = 0; i < 2; i++)
        pos_parity[i].clear();
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        if (p[i] == 1) pos1 = i;
        pos_parity[i & 1].push_back(i);
    }
    for (int i = 0; i < 2; i++)
    sort(pos_parity[i].begin(), pos_parity[i].end(), [&](int posx, int posy) {
        return p[posx] < p[posy];
    });
    int desired_parity = (pos1 & 1) ^ 1;
    int dec_val = n;
    for (auto &c : pos_parity[desired_parity]) {
        q[c] = dec_val--;
    }
    for (auto &c : pos_parity[pos1 & 1]) {
        q[c] = dec_val--;
    }
    for (int i = 1; i <= n; i++) {
        cout << q[i] << " ";
    }
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> t;
    while (t--) solve();
}
