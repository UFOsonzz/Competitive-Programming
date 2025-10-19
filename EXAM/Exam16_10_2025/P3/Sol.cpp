#include <bits/stdc++.h>
using namespace std;
#define fastIO ios_base::sync_with_stdio(false), cin.tie(NULL);
#define FF first
#define SS second
#define eps 1e-9
#define PI aocs(-1.0)
// VECTOR (6)
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) (x).begin(), (x).end()
#define lb lower_bound
#define ub upper_bound
#define uniq(x) sort(all((x))), (x).resize(unique(all((x))) - (x).begin());
// BIT (6)
#define BIT(x, i) (((x)>>(i))&1)
#define MASK(i) (1LL<<(i))
#define CNTBIT(x) __builtin_popcountll(x)
#define ODDBIT(x) __builtin_parityll(x)
#define SUBSET(big, small) (((big)&(small))==(small))
#define FIRSTBIT(x) __builtin_ctzll(x)
//typedef
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> ii;

/* */
template <class T>
bool minimize(T &a, const T &b) {
    if(a > b) {a = b; return 1;}
    return 0;
}
template <class T>
bool maximize(T &a, const T &b) {
    if(a < b) {a = b; return 1;}
    return 0;
}
/* */

/* CODE BELOW */
const int N = 1e5 + 7, M = 1e9 + 7;
const int MOD = 1e9 + 7;
const int oo = 1e9 + 7;

int n, k;
int a[N], b[N];
ll cost[N];

signed main() {
    fastIO;
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];

    ll ans = 0, sum = 0;
    for(int i=1;i<=n;i++) {
        if(a[i] > b[i]) swap(a[i], b[i]);

        int tmpK = k;
        int tmp = min(b[i] - a[i], k);
        int tmpA = a[i] + tmp, tmpB = b[i];
        tmpK-= tmp;

        tmpA+= tmpK / 2;
        tmpB+= tmpK / 2 + (tmpK % 2);

        sum+= 1LL * a[i] * b[i];
        cost[i] = 1LL * tmpA * tmpB;
    }

    for(int i=1;i<=n;i++) {
        maximize(ans, sum - 1LL * a[i] * b[i] + cost[i]);
    }
    cout << ans;

    return 0;
}
