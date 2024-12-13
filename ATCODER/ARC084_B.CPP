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