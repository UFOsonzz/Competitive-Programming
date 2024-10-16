#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int MAXN = 2e5;
const int LG = 19;
const int INF = 1e9;

int n, a[MAXN + 5], last_app[MAXN + 5], suf_unique[MAXN + 5], BIT[MAXN + 5];
bool selected[MAXN + 5];

void UPDATE(int i) {
    while (i <= n) {
        BIT[i]++;
        i += (i & (-i));
    }
}

int GETSUM(int i) {
    int sum = 0;
    while (i > 0) {
        sum += BIT[i];
        i -= (i & (-i));
    }

    return sum;
}

vector<int> ans;
priority_queue<pii> pq_max;
priority_queue<pii, vector<pii>, greater<pii>> pq_min;

void Select(int l, int r, int req, bool even) {
    if (req == 0) return;

    while (r < n && suf_unique[r + 1] - GETSUM(n - r) >= req) {
        ++r;
        pq_max.emplace(a[r], -r);
        pq_min.emplace(a[r], r);
    }

    if (!even) {
        while (selected[pq_max.top().first] || -pq_max.top().second < l)
            pq_max.pop();

        selected[pq_max.top().first] = true;
        UPDATE(n - last_app[pq_max.top().first] + 1);
        ans.push_back(pq_max.top().first);
        Select(-pq_max.top().second + 1, r, req - 1, 1 - even);
    } else {
        while (selected[pq_min.top().first] || pq_min.top().second < l) 
            pq_min.pop();

        selected[pq_min.top().first] = true;
        UPDATE(n - last_app[pq_min.top().first] + 1);
        ans.push_back(pq_min.top().first);
        Select(pq_min.top().second + 1, r, req - 1, 1 - even);
    }
}

void solve() {

    vector<int> compress(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        compress.push_back(a[i]);
    }    

    sort(compress.begin(), compress.end());
    compress.erase(unique(compress.begin(), compress.end()), compress.end());

    for (int i = 1; i <= n; i++) 
        a[i] = lower_bound(compress.begin(), compress.end(), a[i]) - compress.begin();
    
    for (int i = 1; i <= n; i++) {
        last_app[a[i]] = -1;
        suf_unique[i] = 0;
    }

    suf_unique[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        suf_unique[i] = suf_unique[i + 1];

        if (last_app[a[i]] == -1) {
            suf_unique[i]++;
            last_app[a[i]] = i;
        }
    }

    ans.clear();
    for (int i = 0; i <= n; i++)
        BIT[i] = 0, selected[a[i]] = false;

    while (!pq_max.empty()) pq_max.pop();
    while (!pq_min.empty()) pq_min.pop();

    Select(1, 0, (int)compress.size(), 0);

    cout << (int)ans.size() << '\n';
    for (auto c : ans)
        cout << compress[c] << " ";
    cout << '\n';

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("DayCon.inp", "r", stdin);
    freopen("DayCon.out", "w", stdout);

    int t;
    cin >> t;

    while (t--) solve();

}