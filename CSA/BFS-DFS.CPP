#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;

int n, bfs[MAXN + 5], dfs[MAXN + 5];

vector<pair<int, int>> edges;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> bfs[i];

    for (int i = 1; i <= n; i++)
        cin >> dfs[i];

    if (bfs[2] != dfs[2]) return cout << -1, 0;

    for (int i = 2; i <= n; i++) 
        edges.emplace_back(1, bfs[i]);

    for (int i = 2; i < n; i++)
        edges.emplace_back(dfs[i], dfs[i + 1]);
    
    cout << (int)edges.size() << '\n';

    for (auto c : edges) 
        cout << c.first << " " << c.second << '\n';
}

/*
    noi : 1 -> bfs[2, 3, 4, ...n] => dung thu tu bfs nhung chua dung dfs
    noi : dfs[i] -> dfs[i + 1] voi moi i < n => dung thu tu dfs
*/