#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

#define fi first
#define se second

const int MAXN = 1e5;
const int INF = 1e9;

int n, max_doublepath = 0, longest_path[MAXN + 5], longest_up[MAXN + 5];
vector<pii> adj[MAXN + 5];
multiset<int> sub_path[MAXN + 5];

int get(multiset<int>& ms, int cnt) { // tra ve tong cua cnt phan tu lon nhat trong ms
    if (ms.empty()) return 0;
    int total = 0;
    
    for (auto it = --ms.end(); cnt > 0; --it) {
        total += *it;
        --cnt;
        if (it == ms.begin()) break;
    }

    return total;
}

void dfs1(int p, int u) { // xu ly 3 truong hop : 2 duong di deu di qua u va khong di qua p; 
                                            //    mot duong di qua u nhung khong di qua p + mot duong di trong subtree u;
                                            //    2 duong di o trong subtree;
    pair<int, int> two_childpath = {0, 0};

    for (auto& c : adj[u]) {
        if (c.fi == p) continue;
        dfs1(u, c.fi);

        int clongest = (sub_path[c.fi].empty() ? 0 : *sub_path[c.fi].rbegin());
        int longest = clongest + c.se;
        sub_path[u].insert(longest);
        
        longest_path[u] = max(longest_path[u], longest_path[c.fi]);
        if (longest_path[c.fi] > two_childpath.fi) 
            two_childpath = {longest_path[c.fi], two_childpath.fi};
        else if (longest_path[c.fi] > two_childpath.se) 
            two_childpath.se = longest_path[c.fi];

    }

    max_doublepath = max(max_doublepath, two_childpath.fi + two_childpath.se);
    
    int sz = sub_path[u].size();
    auto& paths = sub_path[u];
    
    longest_path[u] = max(longest_path[u], get(paths, min(sz, 2)));
    max_doublepath = max(max_doublepath, get(paths, min(sz, 4))); // truong hop ca 2 duong di deu di qua 1 dinh

    for (auto& c : adj[u]) {
        if (c.fi == p) continue;

        int clongest = (sub_path[c.fi].empty() ? 0 : *sub_path[c.fi].rbegin());
        int longest = clongest + c.se;

        paths.erase(paths.find(longest));
        max_doublepath = max(max_doublepath, longest_path[c.fi] + get(paths, min(sz - 1, 2))); // truong hop mot duong di di qua dinh, va mot duong di trong cay con
        paths.insert(longest);
    }

}

void dfs2(int p, int u) { // xu ly 2 truong hop : mot duong di qua u nhung khong di qua p + mot duong con lai di qua u, p;
                                            //    mot duong di di qua u, p, duong di con lai o trong subtree;
    int sz = sub_path[u].size();
    auto& paths = sub_path[u];

    for (auto& c : adj[u]) {
        if (c.fi == p) continue;

        longest_up[c.fi] = longest_up[u] + c.se;

        int clongest = (sub_path[c.fi].empty() ? 0 : *sub_path[c.fi].rbegin());
        int longest = clongest + c.se;
        paths.erase(paths.find(longest));
        longest_up[c.fi] = max(longest_up[c.fi], c.se + get(paths, min(sz - 1, 1)));
        paths.insert(longest);

        dfs2(u, c.fi);
        
    }

    max_doublepath = max(max_doublepath, longest_up[u] + get(sub_path[u], min(sz, 3))); 

    for (auto& c : adj[u]) {
        if (c.fi == p) continue;

        int clongest = (sub_path[c.fi].empty() ? 0 : *sub_path[c.fi].rbegin());
        int longest = clongest + c.se;
        paths.erase(paths.find(longest));
        max_doublepath = max(max_doublepath, longest_path[c.fi] + get(paths, min(sz - 1, 1)) + longest_up[u]);
        paths.insert(longest);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n;

    int total_length = 0;
    for (int i = 1; i < n; i++) {
        int x, y, d;
        cin >> x >> y >> d;

        adj[x].emplace_back(y, d);
        adj[y].emplace_back(x, d);
        total_length += d;
    }

    dfs1(0, 1);
    dfs2(0, 1);

    int ans = 2 * total_length - max_doublepath;

    cout << ans;
}

/*
    goi 2 thang la A, B
    nhan xet : khong co ly do gi de 2 thang di trung 1 canh nao do -> A di mot phan, B di mot phan (2 cay con)
    trong cay con cua A, de di toi uu thi A se chon duong di dai nhat de di mot lan, cac canh con lai thi 2 lan
    tuong tu voi B
    --> bai toan tro thanh tim 2 duong di co tong lon nhat khong chung canh , ans = 2 * tong cac canh - tong do dai 2 duong di
    ** bai toan tim 2 duong di co tong lon nhat khong chung canh :
    xet cac truong hop : 
    - 2 duong di deu di qua u va khong di qua p; 
    - mot duong di qua u nhung khong di qua p + mot duong di trong subtree u;
    - 2 duong di o trong subtree;
    - mot duong di qua u nhung khong di qua p + mot duong con lai di qua u, p;
    - mot duong di di qua u, p, duong di con lai o trong subtree;

    duy tri tap cac duong di tu cac dinh con den dinh u dai nhat bang set, tinh duong di len tren thi giong dp up/down
*/