#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const char pillar[] = {'A', 'B', 'C'};

int n, pos[MAXN + 1];
vector<pair<char, char>> Move;

void Solve(int disk, int pil) {
    if (disk == 0) return;

    if (pos[disk] == pil) {
        Solve(disk - 1, pil);
    } else {
        Solve(disk - 1, 6 - pil - pos[disk]);
        Move.emplace_back(pillar[pos[disk] - 1], pillar[pil - 1]);
        pos[disk] = pil;
        Solve(disk - 1, pil);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n;

    for (int i = 1; i <= n; i++) {
        char x;
        cin >> x;
        pos[i] = x - 'A' + 1;
    }

    Solve(n, 3);

    cout << (int)Move.size() << '\n';

    for (auto c : Move) 
        cout << c.first << c.second << '\n';
}