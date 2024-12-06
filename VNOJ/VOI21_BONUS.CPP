#include <bits/stdc++.h>

using namespace std;
using ll = long long;


const int MAXN = 3e5 + 5;
const int B = 320;

int n, m, cnt, p[MAXN];
ll dp[MAXN], mxi[MAXN];

string s[MAXN];
vector<int> adj[MAXN];

struct node {
    int nxt[26];
    ll v;
    node() {}
} trie[3 * MAXN];

void add(int i, ll &v) {
    int u = 0;

    for (int j = 0; j < s[i].size(); j++) {
        if (u) v = max(v, trie[u].v);
        int x = s[i][j] - 'A';
        if (!trie[u].nxt[x]) trie[u].nxt[x] = ++cnt;
        u = trie[u].nxt[x];
    }

    v += p[i];
    trie[u].v = max(trie[u].v, v);
}

bool comp(int i, int j) {
    return adj[i].size() > adj[j].size();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int maxn = 0;

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> s[i] >> p[i];
        maxn = max(maxn, p[i]);
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll ans = 0;

    for (int i = 1; i <= maxn; i++)
        sort(adj[i].begin(), adj[i].end(), comp);

    for (int i = n; i >= 1; i--) {
        ll v = 0;

        if ((int)adj[p[i]].size() <= B)
            for (auto c: adj[p[i]]) 
                v = max(v, dp[c]);
        else v = max(v, mxi[p[i]]);

        add(i, v);
        for (int j = 0; j < adj[p[i]].size(); j++) {
            if ((int)adj[adj[p[i]][j]].size() <= B) break;
            mxi[adj[p[i]][j]] = max(mxi[adj[p[i]][j]], v);
        }

        dp[p[i]] = max(dp[p[i]], v);
        ans = max(ans, v);
    }

    cout << ans;
}

/*
    dp[i] : cach chon co tong lon nhat ket thuc o vi tri i
    Y TUONG : PHAN XU LY XAU -> SU DUNG TRIE
    PHAN XU LY CAC QUAN HE (pi, pj) : CHIA CAN 2 NHOM
    B = O(sqrt(n))
    Nhom 1 : degree(i) < B 
    => voi moi thang i nay ta for het cac thang ke no -> tinh duoc dp
    Nhom 2 : degree(i) > B
    => chi ton tai <= n/B thang nhu nay (co the coi nhom nay la nhom n/B gia tri dac biet)
    -> khi tinh dp[j] voi j bat ky thi ta luon xet xem j co cap nhat cho cac thang trong so n/B thang nay khong

    => TINH DUOC DP
*/
