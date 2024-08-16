#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 1e11 + 3;
const ll base = 9973;
const int MAXN = 5e4;

ll base_pw[MAXN + 5], sqbase[MAXN + 5], divi[MAXN + 5], modu[MAXN + 5];

ll Mul(ll x, int y) {
    if (sqbase[y] == 0) return 0;

    return (x * sqbase[y] % mod * divi[y] + x * modu[y]) % mod;
}

int n, Ans = 1, sz[MAXN + 5], a[MAXN + 5];
bool Selected[MAXN + 5];
vector<int> adj[MAXN + 5];


int dfs_sz(int p, int u) {
    sz[u] = 1;
    for (auto& c : adj[u]) {
        if (c == p || Selected[c]) continue;
        sz[u] += dfs_sz(u, c);
    }

    return sz[u];
}

int Centroid(int p, int u, int Tot) {
    for (auto& c : adj[u]) {
        if (c == p || Selected[c]) continue;
        if (sz[c] * 2 > Tot) 
            return Centroid(u, c, Tot);
    }

    return u;
}

int Bslen, Depth[MAXN + 5];
ll Root[MAXN + 5], nonRoot[MAXN + 5], revRoot[MAXN + 5];
gp_hash_table<ll, bool> nonRootmp;
vector<int> path, cache;

void Clear_data() {
    nonRootmp.clear();
    path.clear();
    cache.clear();
}

int rt;
bool rev_loop;

bool Check(int p, int u) {
    path.push_back(u);
 
    if (u == rt) {
        Depth[u] = 0;
        nonRoot[u] = 0;

        Root[u] = revRoot[u] = a[u] % mod;

    } else {
        
        Depth[u] = Depth[p] + 1;

        Root[u] = (Mul(Root[p], 1) + a[u]) % mod;
        nonRoot[u] = (Mul(nonRoot[p], 1) + a[u]) % mod;
        revRoot[u] = (Mul(a[u], Depth[u] - Depth[rt]) + revRoot[p]) % mod;

        // ben nay dai hon ben kia :
        // ben nay lay root, ben kia lay nonroot
        
        int Other_len = Bslen - (Depth[u] + 1);
    
        if (Other_len > 0 && Other_len < Depth[u] + 1 && 
            nonRootmp.find((Root[u] - Mul(Root[path[Depth[u] - Other_len]], Other_len) + mod) % mod) != nonRootmp.end() &&
            Root[path[Depth[u] - Other_len]] == revRoot[path[Depth[u] - Other_len]])
            return true;

        // hoan toan o ben nhanh nay : 
        if (Depth[u] + 1 >= Bslen && Root[u] == revRoot[u])
            return true;
        cache.push_back(u);

    }

    if (rev_loop == false) {
        for (int i = 0; i < adj[u].size(); i++) {
            int& c = adj[u][i];
            if (c == p || Selected[c]) continue;
            
            if (Check(u, c)) return true;
            if (u == rt) {
                for (auto& v : cache) 
                    nonRootmp[nonRoot[v]] = true;
                
                cache.clear();
            }
        }
    } else {
        for (int i = adj[u].size() - 1; i >= 0; i--) {
            int& c = adj[u][i];
            if (c == p || Selected[c]) continue;
            
            if (Check(u, c)) return true;
            if (u == rt) {
                for (auto& v : cache) 
                    nonRootmp[nonRoot[v]] = true;
                
                cache.clear();
            }
        }
    }

    path.pop_back();
    return false;
}

void Build(int u) {
    int Tot = dfs_sz(-1, u);
    int Cen = Centroid(-1, u, Tot);
    
    rt = Cen;    

    int mid, left = 1, right = n / 2;

    while (left <= right) {
        mid = (left + right) / 2;
        Bslen = 2 * mid;
        
        Clear_data();
        rev_loop = false;
        bool ok = Check(-1, Cen);

        if (!ok) {
            Clear_data();
            rev_loop = true;
            ok = Check(-1, Cen);
        }
        
        if (ok) {
            Ans = max(Ans, Bslen);
            left = mid + 1;
        } else right = mid - 1;
        
    }

    left = 1, right = n / 2;

    while (left <= right) {
        mid = (left + right) / 2;
        Bslen = 2 * mid + 1;

        Clear_data();
        rev_loop = false;
        bool ok = Check(-1, Cen);

        if (!ok) {
            Clear_data();
            rev_loop = true;
            ok = Check(-1, Cen);
        }

        
        if (ok) {
            Ans = max(Ans, Bslen);
            left = mid + 1;
        } else right = mid - 1;
        
    }

    Selected[Cen] = true;
    for (auto& c : adj[Cen])
        if (!Selected[c]) Build(c);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    base_pw[0] = 1LL;

    for (int i = 1; i <= MAXN; i++)
        base_pw[i] = base_pw[i - 1] * base % mod;

    for (int i = 0; i <= MAXN; i++) {
        sqbase[i] = sqrt(base_pw[i]);
        divi[i] = base_pw[i] / sqbase[i];
        modu[i] = base_pw[i] % sqbase[i];
    }

    cin >> n;
    for (int i = 1; i <= n; i++) {
        char x;
        cin >> x;
        a[i] = (int)x;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Build(1);

    cout << Ans;
}

/*
    Centroid cat duong : 
    Moi nhanh node trong mot lan xu ly cay con trong centroid luu mot mang hash tu goc, mot mang hash tu node con truc tiep cua goc, mot mang hash nguoc tu goc 
    va kiem tra 2 truong hop : nhanh ta dang xet dai hon nhanh kia, toan bo palindrome nam trong nhanh nay, (reverse mang ke de lam cac truong hop con lai)
    **Bai bop thoi gian nen neu code ko du gon thi phai dung gp_hash_table**
*/