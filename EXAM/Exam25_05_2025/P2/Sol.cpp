#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e4;

int n, a[MAXN + 5], pre[MAXN + 5], First[8];

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		pre[i] = (pre[i - 1] + a[i]) % 7;
	}

	for (int i = 0; i <= 6; i++)
		First[i] = -1;

	int ans = 0;
	for (int i = 0; i <= n; i++)
		if (First[pre[i]] == -1)
			First[pre[i]] = i;
		else ans = max(ans, i - First[pre[i]]);

	cout << ans;
}

