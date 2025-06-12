#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5;

int n, deg[2 * MAXN + 5];
pair<int, int> a[MAXN + 5];
vector<int> adj[2 * MAXN + 5], Eulercycle;
bool vis[MAXN + 5], visNode[2 * MAXN + 5];

int itr(vector<int>& x, int val) {
    return lower_bound(x.begin(), x.end(), val) - x.begin();
}

void findEuler(int u, int incoming_id) {
    while (!adj[u].empty()) {
        int id = adj[u].back();
        if (vis[id]) {
            adj[u].pop_back(); 
            continue;
        }

        int dest = a[id].first + a[id].second - u;
        vis[id] = true;
        adj[u].pop_back();
        findEuler(dest, id);
    }

    if (incoming_id != -1) 
        Eulercycle.push_back(incoming_id);
}

void visAll(int u) {
    visNode[u] = true;
    for (int id : adj[u]) {
        int dest = a[id].first + a[id].second - u;
        if (visNode[dest])
            continue;
        visAll(dest);
    }
}

void solve() {
    cin >> n;
    
    vector<int> fi_comp(0), se_comp(0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
        fi_comp.push_back(a[i].first);
        se_comp.push_back(a[i].second);
    }

    sort(fi_comp.begin(), fi_comp.end());
    sort(se_comp.begin(), se_comp.end());

    fi_comp.erase(unique(fi_comp.begin(), fi_comp.end()), fi_comp.end());
    se_comp.erase(unique(se_comp.begin(), se_comp.end()), se_comp.end());

    int gn = fi_comp.size(), gm = se_comp.size();

    for (int i = 1; i <= n; i++) {
        a[i].first = itr(fi_comp, a[i].first);
        a[i].second = itr(se_comp, a[i].second) + gn;
        adj[a[i].first].push_back(i);
        adj[a[i].second].push_back(i);
        deg[a[i].first]++;
        deg[a[i].second]++;
    }

    bool Connected = true;
    visAll(0);
    for (int i = 0; i < gn + gm; i++)
        if (!visNode[i])
            Connected = false;

    // for (int i = 1; i <= n; i++) {
    //     cout << a[i].first << " " << a[i].second << '\n';
    // }

    int oddCount = 0;
    vector<int> oddDeg(0);
    for (int i = 0; i < gn + gm; i++) {
        if (deg[i] % 2) {
            oddCount++;
            oddDeg.push_back(i);
        }
    }
    
    // for (auto c : oddDeg) {
    //     cout << c << " ";
    // }
    // cout << '\n';
    if (oddCount == 1 || oddCount > 2 || !Connected) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        bool Cycle = true;
        if (oddCount == 2) {
            Cycle = false;
            adj[oddDeg[0]].push_back(0);
            adj[oddDeg[1]].push_back(0);
            a[0] = {oddDeg[0], oddDeg[1]};
            deg[oddDeg[0]]++;
            deg[oddDeg[1]]++; 
        }

        findEuler(0, -1);
        if (Cycle) {
            for (auto c : Eulercycle)
                cout << c << " ";
            cout << '\n';
        } else {
            int extra_pos = 0;
            for (int i = 0; i < Eulercycle.size(); i++)
                if (Eulercycle[i] == 0) {
                    extra_pos = i;
                    break;
                }

            for (int i = extra_pos + 1; i < Eulercycle.size(); i++) {
                cout << Eulercycle[i] << " ";
            }

            for (int i = 0; i < extra_pos; i++) {
                cout << Eulercycle[i] << " ";
            }

            cout << '\n';
                
        }
    }

    for (int i = 0; i < gn + gm; i++)
        adj[i].clear(), deg[i] = 0, visNode[i] = false;
    Eulercycle.clear();
    for (int i = 0; i <= n; i++)
        vis[i] = false;
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
    tao do thi co cac dinh la (a[i].first, 1), (a[i].second, 2)
    canh noi 2 dinh (a[i].first, 1) va (a[i].second, 2) dai dien cho a[i]
    -> 1 duong di euler tren do thi nay dai dien cho 1 beautiful melody
*/