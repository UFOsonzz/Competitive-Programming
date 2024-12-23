#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1e5 + 5;
const int LG = 18;
const ll INF = 1e18;

int n, q, l[MAXN], r[MAXN];
ll h[MAXN], pfx[MAXN], res[MAXN];

pair<ll, int> sfx[MAXN][LG];

ll Calc_sfx(int l, int r) {
    if (l > r) return 0;
    ll ans = 0;

    for (int t = LG - 1; t >= 0; t--) {
        if (sfx[l][t].second <= r) {
            ans += sfx[l][t].first;
            l = sfx[l][t].second;
        }
    }

    ans += h[l] * (r - l + 1);
    return ans;
}

void Dnc_opt(int tl, int tr, int optl, int optr) {
    if (tl > tr) return;
    int tm = (tl + tr) / 2;

    // Find optm
    int optm = optl;
    ll opt_ans = INF;

    for (int i = optl; i <= min(tm, optr); i++) {
        ll ans_i = pfx[i] + Calc_sfx(i + 1, tm);
        if (ans_i < opt_ans) {
            opt_ans = ans_i;
            optm = i;
        }
    }

    res[tm] = opt_ans;
    Dnc_opt(tl, tm - 1, optl, optm);
    Dnc_opt(tm + 1, tr, optm, optr);
}

int main() {
    freopen("valley.inp", "r", stdin);
    freopen("valley.out", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        cin >> h[i];

    stack<int> st;

    for (int i = 1; i <= n; i++) {
        while (!st.empty() && h[st.top()] <= h[i])
            st.pop();

        l[i] = (st.empty() ? 0 : st.top());
        st.push(i);
    }

    while (!st.empty()) st.pop();

    for (int i = n; i >= 1; i--) {
        while (!st.empty() && h[st.top()] <= h[i])
            st.pop();
        
        r[i] = (st.empty() ? n + 1 : st.top());
        st.push(i);
    }
    
    for (int i = 1; i <= n; i++) {
        pfx[i] = pfx[l[i]] + h[i] * (i - l[i]);
        sfx[i][0] = {h[i] * (r[i] - i), r[i]};
    }

    sfx[n + 1][0] = {0, n + 1};

    for (int lg = 1; lg < LG; lg++) {
        sfx[n + 1][lg] = {0, n + 1};
        
        for (int i = 1; i <= n; i++) {
            ll fi = sfx[i][lg - 1].first + sfx[sfx[i][lg - 1].second][lg - 1].first;
            int se = sfx[sfx[i][lg - 1].second][lg - 1].second;
            sfx[i][lg] = {fi, se};
        }
    }

    Dnc_opt(1, n, 1, n);
    
    ll Pfx_sum = 0;
    for (int i = 1; i <= n; i++) {
        Pfx_sum += h[i];
        res[i] -= Pfx_sum;
    }

    while (q--) {
        int k;
        cin >> k;

        cout << res[k] << '\n';
    }
}
