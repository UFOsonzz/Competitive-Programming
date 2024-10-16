
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, a[N], ans_max, ans_min, match_num, leaves;
vector<int> adj[N], roll;
bool vis[N], match[N];

void dfs(int u) {
    vis[u] = true;
    int cnt = 0;
    for (auto c: adj[u]) {
        ++cnt;
        if (!vis[c]) {
            dfs(c);
            if (!match[u] && !match[c])
                match[c] = match[u] = true,
                match_num++;
        }
    }
    if (!cnt) leaves++;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        adj[a[i]].push_back(i);
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        roll.resize(0);
        match_num = leaves = 0;
        int u = i;
        while (!vis[u]) {
            vis[u] = true;
            roll.push_back(u);
            u = a[u];
        }
        for (auto c: roll) vis[c] = false;
        vis[u] = true;
        roll.resize(0);
        roll.push_back(u);
        for (int j = a[u]; j != u; j = a[j]) {
            roll.push_back(j);
            vis[j] = true;
        }
        bool branch = false;
        for (auto c: roll) {
            if (adj[c].size() > 1) branch = true;
            dfs(c);
        }
        if (branch || roll.size() == 1) ans_max += leaves;
        else ans_max += 1;
        int m = roll.size();
        u = 0;
        for (int j = 0; j < m; j++) if (match[roll[j]]) {
            u = j;
            break;
        }
        if (match[roll[u]]) {
            int cur = 0, j = u;
            do {
                if (!match[roll[j]]) cur++;
                else match_num += cur/2, cur = 0;
                j = (j + 1)%m;
            } while (j != u);
            match_num += cur/2;
        } else ans_min += (m+1)/2;
        ans_min += match_num;
    }
    ans_max = n - ans_max;
    cout << ans_min << " " << ans_max;
}
/*
**do thi cua bai toan la tap hop cac do thi mat troi**
**truong hop thuong vong toi da**
- chi co cac node leaves la con song, ngoai tru cac truong hop dac biet sau:
do thi mat troi dang xet chi co 1 node tu ban minh -> ans_max = 1
do thi mat troi dang xet chi co vong tron -> ans_max = size - 1 ( chi con mot node con song )
**truong hop thuong vong toi thieu**
- ghep nhieu cap nhat co the, bat dau voi viec ghep cap cac node tren cac nhanh la cay tu la len goc
-> sau khi ghep truoc cac cap tren cay thi vong tron co the co mot so node da bi ghep cap roi -> vong tron co the bi chia ra thanh cac doan thang -> so cap = size / 2
- neu vong tron ton tai 1 node da bi ghep cap -> thuong vong toi thieu = tong so cap cua cac doan thang bi tach ra
- neu vong tron khong co node nao bi ghep cap -> thuong vong toi thieu = (size vong tron + 1) / 2 ( neu vong tron co chan phan tu thi giai quyet bthg,
                                                                                                   neu vong tron co le phan tu thi ghep cap se thua ra 1 phan tu va thuong vong = so cap + 1 )
- neu do thi chi con 1 node tu ban minh -> ans_min = 1
*/