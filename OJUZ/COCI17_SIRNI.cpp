#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, Weight;

    Edge() {}
    Edge(int u, int v, int Weight) :
        u(u), v(v), Weight(Weight) {}
    
    bool operator < (const Edge& other) const {
        return Weight < other.Weight;
    }
};

const int MAXN = 1e5;
const int MAXP = 1e7;

int n, nxt[MAXP + 5], Dsu_pa[MAXN + 5];
vector<int> p;
vector<Edge> Ed;

void Init_Dsu() {
    for (int i = 0; i < n; i++) 
        Dsu_pa[i] = i;
}

int Find_pa(int u) {
    if (u == Dsu_pa[u]) return u;
    return Dsu_pa[u] = Find_pa(Dsu_pa[u]);
}

bool Dsu_Union(int u, int v) {
    u = Find_pa(u);
    v = Find_pa(v);

    if (u == v) return false;

    Dsu_pa[v] = u;
    return true;
}

int main() {
    cin.tie(0) -> ios::sync_with_stdio(0);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        p.push_back(x);
    }

    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    n = p.size();

    for (int i = 0; i < n - 1; i++) {
        nxt[p[i]] = i;
        for (int j = p[i] + 1; j < p[i + 1]; j++)
            nxt[j] = i + 1;
    }

    nxt[p[n - 1]] = n - 1;

    for (int i = 0; i < n; i++) {
        Ed.emplace_back(i, nxt[p[i] + 1], p[nxt[p[i] + 1]] % p[i]);
        for (int mul = 2 * p[i]; mul <= p[n - 1]; mul += p[i]) {
            Ed.emplace_back(i, nxt[mul], p[nxt[mul]] % p[i]);
            mul = p[nxt[mul]] / p[i] * p[i];
        }
    }

    sort(Ed.begin(), Ed.end());

    Init_Dsu();

    int Ans = 0;
    for (auto& c: Ed) 
        if (Dsu_Union(c.u, c.v)) 
            Ans += c.Weight;
    
    cout << Ans;
}
/*
    Chuyen ve bai toan tim mst. 
    Nhan xet : Ta khong can xet het O(n^2) canh ma chi can xet voi moi p[i] (sau khi sort) cac thang p[j] gan nhat voi mot boi mul cua no 
    sau do mul nhay den p[j] - (p[j] % p[i]) de giam bot do phuc tap
*/