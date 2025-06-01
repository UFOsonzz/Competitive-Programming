#include <bits/stdc++.h>
 
#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
#define gsize(x) (int)((x).size())
 
const char nl = '\n';
typedef long long ll;
typedef long double ld;
 
using namespace std;
 
void solve() {
    ll n, k;
    cin >> n >> k;
    
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    ll lb = 0, ub = *max_element(all(a)) + k, ans = 0;
    while (lb <= ub) {
        ll tm = (lb + ub) / 2;
        bool good = false;
        
        for (int i = 0; i < n; i++) {
            vector<ll> min_needed(n);
            min_needed[i] = tm;
            
            ll c_used = 0;
            for (int j = i; j < n; j++) {
                if (min_needed[j] <= a[j]) break;
                
                if (j + 1 >= n) {
                    c_used = k + 1;
                    break;
                }
                
                c_used += min_needed[j] - a[j];
                min_needed[j + 1] = max(0LL, min_needed[j] - 1);
            }
            
            if (c_used <= k) good = true;
        }
        
        if (good) {
            ans = tm;
            lb = tm + 1;
        } else {
            ub = tm - 1;
        }
    }
    
    cout << ans << nl;
}
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int T = 1;
	while (T--) solve();
}