#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define fi first
#define se second
int x;
vector<pii> fact;
vector<int> res[6969];
vector<int> Solve(int x) {
    vector<int> ret;
    for (int i = 1; i <= fact[x].se; i++) {
        ret.push_back(fact[x].fi);
        if (x > 0) {
            if (i & 1) {
                for (int i = res[x - 1].size() - 1; i >= 0; i--) 
                    ret.push_back(-res[x - 1][i]);
            } else {
                for (auto c: res[x - 1])
                    ret.push_back(c);
            }
        }
    }
    return ret;
}
int main() {
    cin >> x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            fact.emplace_back(i, 0);
            while (x % i == 0) {
                fact.back().se++;
                x /= i;
            }
        }
    }
    if (x > 1) fact.emplace_back(x, 1);
    for (int i = 0; i < fact.size(); i++) {
        if (i > 0) res[i] = res[i - 1];
        vector<int> tmp = Solve(i);
        for (auto c: tmp) res[i].push_back(c);
    }
    int cur = 1;
    cout << cur << " ";
    for (auto c: res[(int)fact.size() - 1]) {
        if (c > 0) cur *= c;
        else cur /= -c;
        cout << cur << " ";
    }
    
}