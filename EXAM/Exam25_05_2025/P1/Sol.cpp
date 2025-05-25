#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll LIM = 1e12;

int main() {
    ll n;
    cin >> n;
    
    int ans = 0;
    vector<pair<int, int>> factors;
    for (int i = 2; (ll)i * i <= LIM; i++) {
        if (n % i == 0) {
            int pw = 0;
            while (n % i == 0) {
                n /= i;
                pw++;
            }

            factors.emplace_back(i, pw);

            int sq = (int)sqrt(2 * pw);
            if (sq * (sq + 1) > 2 * pw) 
                --sq;
            ans += sq;
        }
    }

    if (n > 1) ans++;   

    cout << ans;
}