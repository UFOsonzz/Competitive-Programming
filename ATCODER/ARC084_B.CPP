#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;

int n, d[MAXN];
vector<pair<int, int>> adj[MAXN];

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void dijkstra() {

    pq.emplace(1, 1);
    memset(d, 0x3f, sizeof d);

    d[1] = 1;

    while (!pq.empty()) {
        int x = pq.top().second;
        int dis = pq.top().first;
        pq.pop();

        if (dis > d[x]) continue;

        for (auto y : adj[x]) {
            if (d[y.first] > d[x] + y.second) {
                d[y.first] = d[x] + y.second;
                pq.emplace(d[y.first], y.first);
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i) 
        adj[i].emplace_back((i + 1) % n, 1);

    for (int i = 1; i < n; ++i) 
        adj[i].emplace_back(i * 10 % n, 0);
    
    dijkstra();

    cout << d[0];
}

/*
    Mot so luon duoc construct tu 2 thao tac sau
        - Cong 1 -> voi thao tac nay thi tong digit += 1
        - Nhan 10 -> voi thao tac nay thi tong digit khong doi

    => Construct mot so theo 2 thao tac nay thi ta co the biet duoc tong digit luon
    Dung do thi vo han dinh : 
    dinh x noi canh 1 chieu den x + 1 trong so 1, x noi canh 1 chieu den 10x trong so 0

    => Dap an la duong di ngan nhat den mot boi cua K
    ** Toi uu xuong k dinh 
    - Nhan xet : ta chi quan tam den x mod K vi ta chi can tim duong den boi
    => dinh x noi canh den dinh (x + 1) % K trong so 1
    => dinh x noi canh den dinh 10x % K trong so 0
    => tim duong di ngan nhat tu dinh 1 den di 0, dap an la do dai duong di + 1 (1 nay la cua thang 1)
*/