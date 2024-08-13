#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
const int MAXM = 2e5;

int n, m, Q, Dsu_pa[MAXN + 5];
set<int> InAdj[MAXN + 5], OutAdj[MAXN + 5];

int Find_Root(int u) {
    if (u == Dsu_pa[u]) return u;
    return Dsu_pa[u] = Find_Root(Dsu_pa[u]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        InAdj[y].insert(x);
        OutAdj[x].insert(y);
    }

    for (int i = 1; i <= n; i++)
        Dsu_pa[i] = i;

    queue<int> q;
    for (int i = 1; i <= n; i++) 
        if (OutAdj[i].empty()) 
            q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        Dsu_pa[u] = 0;
        for (auto c : InAdj[u]) {
            OutAdj[c].erase(u);
            if (OutAdj[c].empty()) q.push(c);
        }
    }

    for (int i = 1; i <= n; i++) 
        if ((int)OutAdj[i].size() == 1) q.push(i);

    // Moi Dsu la mot node --> q nay luu dsu chu ko phai luu node
    while (!q.empty()) {
        int u = Find_Root(q.front());
        q.pop();
        if ((int)OutAdj[u].size() != 1) continue;

        int v = *OutAdj[u].begin();
       
        v = Find_Root(v);

        if (u == v) continue;
        InAdj[v].erase(u);
        OutAdj[u].clear();

        if (InAdj[u].size() + OutAdj[u].size() < InAdj[v].size() + OutAdj[v].size()) 
            swap(u, v);
        
        // Coi nhu xoa node v va tro tat ca inadj[v] toi u
        for (auto c : InAdj[v]) {

            InAdj[u].insert(c);
            OutAdj[c].insert(u);
            OutAdj[c].erase(v);

            if ((int)OutAdj[c].size() == 1)
                q.push(c);
        }

        // Coi nhu xoa node v va tat ca thang duoc v tro toi se coi nhu duoc u tro toi
        for (auto c : OutAdj[v]) {
            OutAdj[u].insert(c);
            InAdj[c].insert(u);
            InAdj[c].erase(v);
        }

        InAdj[v].clear();
        OutAdj[v].clear();
        Dsu_pa[v] = u;
    }

    cin >> Q;

    while (Q--) {
        int u, v;
        cin >> u >> v;

        if (min(Dsu_pa[u], Dsu_pa[v]) == 0 || Find_Root(u) == Find_Root(v))
            cout << 'B';
        else cout << 'H'; 
    }
}
/*
    Giai bai toan bang cach toi gian do thi
    - Lap di lap lai viec xoa cac node khong co canh di ra boi vi di vao do thi B chac chan thang
    -> do thi bay gio chi con cac node co >= 1 canh di ra
    - Gia su node a la node chi co 1 canh di ra node b thi ta co thi gop a va b thanh 1 node 
        boi vi neu di vao a thi buoc tiep theo chac chan phai di vao b
    - Gop cac node bang Dsu va moi lan gop 2 set thi se truyen ca InAdj va OutAdj cho set cha
    ** Cac truong hop co the cai dat sai : **
        + Insert node u vao set InAdj[u] hoac OutAdj[u] --> Khi union 2 node u, v (canh u -> v) thi tot nhat la xoa u khoi InAdj[v] va xoa v khoi OutAdj[u]
        + Xet gop cap v, u (canh v -> u) va sau khi so sanh size thi ta gop het vao set cua v va clear set cua u nhung van chua xet cap u, c (canh u -> c)
        --> Xu ly bang cach xet u = Find_Root(u) tu dau luon
*/