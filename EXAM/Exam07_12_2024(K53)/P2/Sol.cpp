#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
const int INF = 1e9;

void Insert(pair<int, int> p, set<pair<int, int>>& s) {
    if (p.first > p.second) return;
    s.insert(p);
}

void solve() {
    string s;
    cin >> s;

    set<pair<int, int>> SimSeg;

    int st = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] != s[st]) 
            SimSeg.emplace(st, i - 1), st = i;
    }

    SimSeg.emplace(st, (int)s.size() - 1);

    int q;
    cin >> q;

    while (q--) {
        int id, i;
        cin >> id >> i;
        if (id == 1) {
            auto it = (--SimSeg.upper_bound(make_pair(i, INF)));
            cout << it->second - it->first + 1 << '\n';
        } else {
            auto it = (--SimSeg.upper_bound(make_pair(i, INF)));
            int fi = it->first;
            int se = it->second;
            SimSeg.erase(it);
            Insert(make_pair(fi, i - 1), SimSeg);
            Insert(make_pair(i + 1, se), SimSeg);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int TestNum;
    cin >> TestNum;

    for (int i = 1; i <= TestNum; i++) {
        cout << "Case " << i << ":\n";
        solve();
    }

}

// Duy tri set cac pair (l, r) -> cac doan lien tiep bang nhau