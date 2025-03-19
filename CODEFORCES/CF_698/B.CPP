#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;

int n, a[MAXN], pa[MAXN], sz[MAXN];

vector<int> cycle;

int find_set(int u) {
    if (u == pa[u])
        return u;
    return pa[u] = find_set(pa[u]);
}

bool union_set(int u, int v) {
    u = find_set(u);
    v = find_set(v);

    if (u == v)
        return false;
    
    if (sz[u] < sz[v])
        swap(u, v);

    sz[u] += sz[v];
    pa[v] = u;

    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;

    int cyclic_root = -1, cycle_num = 0;

    for (int i = 1; i <= n; i++)
        pa[i] = i, sz[i] = 1;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == i)
            cyclic_root = i;
        if (!union_set(i, a[i])) 
            cycle.push_back(i), cycle_num++;
    }

    if (cyclic_root != -1) {
        cout << cycle_num - 1 << '\n';
    } else {
        cout << cycle_num << '\n';
    }

    for (int i = 0; i < cycle.size(); i++) {
        if (cycle[i] == cyclic_root) {
            swap(cycle[i], cycle[0]);
            break;
        }
    }

    for (int i = 0; i < cycle.size(); i++) 
        a[cycle[i]] = cycle[0];

    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
}

/*
    do thi se co dang mot tap cac do thi mat troi
    voi moi do thi mat troi break mot canh trong cycle va noi no den mot cycle cua mot do thi mat troi root
    cuoi cung thi break mot canh trong cycle cua do thi mat troi root roi tu noi den chinh no
    chon do thi mat troi root : 
        neu chon mot do thi mat troi co cycle tu noi den chinh no thi buoc cuoi ko can break -> loi 1 step
    => neu co cycle size 1 thi ans = so do thi mat troi - 1, khong thi ans = so do thi mat troi
*/