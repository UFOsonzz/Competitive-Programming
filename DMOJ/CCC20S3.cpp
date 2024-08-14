#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const ll m1 = 1e9 + 7, m2 = 1e9 + 9;
const ll p = 9973;

string n , h;
int d[250], target[250];
ll poly1, poly2, pow1, pow2;
set<pll> good;

int main() {
    cin >> n >> h ;

    if (h.size() < n.size()) return cout << 0, 0;
    pow1 = 1; pow2 = 1;

    for (int i = 0; i < n.size(); i++) {

        d[h[i]]++; target[n[i]]++;
        poly1 = (poly1 * p + h[i]) % m1;
        poly2 = (poly2 * p + h[i]) % m2;

        pow1 = pow1 * p % m1;
        pow2 = pow2 * p % m2;

    }

    bool match = true;
    for (int i = 'a'; i <= 'z'; i++) {
        if (d[i] != target[i]) match = false;
    }

    if (match == true) {
        good.insert({poly1, poly2});
    }

    for (int i = n.size(); i < h.size(); i++) {

        d[h[i]]++; d[h[i - n.size()]]--;
        poly1 = ((poly1 * p - pow1 * h[i - n.size()]) % m1 + h[i] + m1) % m1;
        poly2 = ((poly2 * p - pow2 * h[i - n.size()]) % m2 + h[i] + m2) % m2;
        match = true;

        for (int i = 'a'; i <= 'z'; i++) {
            if (d[i] != target[i]) match = false;
        }

        if (match == true) good.insert({poly1, poly2});
    }
    
    cout << good.size();

}