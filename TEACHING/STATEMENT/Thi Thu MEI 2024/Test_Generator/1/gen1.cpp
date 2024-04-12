#include <bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll get(ll l, ll r) {
    return l + rng() % (r - l + 1);
}
ll a, b, c;
vector<ll> divList;
ll random_div(ll x) {
    divList.clear();
    for (ll i = 1; i * i <= x; i++) {
        if (x % i == 0) divList.push_back(i), divList.push_back(x / i);
    }
    return divList[get(0, divList.size() - 1)];
}
int main() {
    for (int i = 1; i <= 50; i++) {
        string cur_name = "XY" + to_string(i) + ".inp";
        ofstream inp(cur_name);
        if (i <= 20) {
            c = get(1, 5000);
            ll tmp = get(1, c);
            a = random_div(tmp);
            b = random_div(c - tmp);
            inp << a << " " << b << " " << c;
        } else if (i <= 40) {
            c = get(1, 1e5);
            ll tmp = get(1, c);
            a = random_div(tmp);
            b = random_div(c - tmp);
            inp << a << " " << b << " " << c;
        } else {
            a = get(1, 1e6);
            b = get(1, 1e6);
            c = a * get(0, 5e11) + b * get(0, 5e11);
            inp << a << " " << b << " " << c;
        }
    }
}