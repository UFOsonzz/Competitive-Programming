#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int x;
vector<int> sol;
map<int, bool> exi;
void solve() {
    sol.clear();
    exi.clear();
    cin >> x;

    int st_num = 0, cur_val = 0;
    for (int i = 0; i <= x; i += 2) {
        int eval = __builtin_popcount(i);
        if (eval < cur_val) continue;
        cur_val = eval;
        st_num = i;
    }
    sol.push_back(st_num);
    for (int i = 1; i < 30; i++) {
        if (st_num & (1 << i)) {
            int new_val = (st_num ^ (1 << i)) | (1 << (i - 1));
            st_num = new_val;
            sol.push_back(st_num);
        }
    }
    /*
    for (int i = 0; i < sol.size(); i++) {
        int cur = sol[i];
        for (int j = i; j < sol.size(); j++) {
            cur &= sol[j];
            if (exi.find(cur) != exi.end()) return cout << "INVALID AT " << i << " " << j << " " << cur << " " << sol[i] << " " << sol[j] << '\n', void();
            exi[cur] = 1;
        }
    }
    */
    cout << sol.size() << '\n';
    for (auto c: sol) cout << c << " ";
    cout << '\n';
}
int main() {
    int t;
    cin >> t;
    while (t--) solve();
}
