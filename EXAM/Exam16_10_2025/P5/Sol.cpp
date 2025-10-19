#include "bits/stdc++.h"
using namespace std;

#define ll long long

const int MOD = 1e9+7;
const int INF = 1e9;

/**
 * bfs
 * idea:
 * - we know that the path length is fixed, that is 2*n - 1
 * - we do 2*n - 2 iterations to build the path.
 * - in each iteration, we do the following:
 *  - find the minimum character of all the next possible positions
 *  - add those candidates positions
 *  - append the minimum character to the result
 */
void solve() {
  int n;
  cin >> n;
  vector<string> g(n);
  for (int i = 0; i < n; i++) {
    cin >> g[i];
  }
  int m = 2 * n - 2;
  int dx[] = {0, 1};
  int dy[] = {1, 0};
  vector<vector<bool>> vis(n, vector<bool>(n));
  vector<array<int, 2>> cur;
  cur.push_back({0, 0});
  vis[0][0] = true;
  string res;
  res += g[0][0];
  while (m--) {
    vector<array<int, 2>> nxt;
    char mn = 'Z';
    for (auto [x, y] : cur) {
      for (int i = 0; i < 2; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < n && ny < n) {
          mn = min(mn, g[nx][ny]);
        }
      }
    }
    for (auto [x, y] : cur) {
      for (int i = 0; i < 2; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < n && ny < n && g[nx][ny] == mn && !vis[nx][ny]) {
          nxt.push_back({nx, ny});
          vis[nx][ny] = true;
        }
      }
    }
    cur = move(nxt);
    res += mn;
  }
  cout << res << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);

  // freopen("input.in", "r", stdin);
  // freopen("output.out", "w", stdout);

  // int T = 1;
  // cin >> T;
  // while (T--) {
    solve();
  // }

  return 0;
}