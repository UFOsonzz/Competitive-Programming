
#include <bits/stdc++.h>
using namespace std;
#define inp cout
using ll = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll get(ll x, ll y) {
    return x + rng() % (y - x + 1);
}
const int N = 2e5 + 5;
int n, a[N];
int main() {
    ios::sync_with_stdio(0);
    cout.tie(0);

    for (int Test = 1; Test <= 50; Test++) {
        string cur_name = "DC" + to_string(Test) + ".inp";
        ofstream inp(cur_name);
        if (Test <= 20) n = get(1, 300);
        else if (Test <= 40) n = get(1, 5000);
        else n = get(1, N - 5);
        ll sum = 0;
        for (int i = 1; i <= n; i++)
            a[i] = get(-1e9, 1e9), sum += a[i];
        if (sum > 0) {
            for (int i = 1; i <= n; i++)
                a[i] = -a[i];
        }
        inp << n << '\n';
        for (int i = 1; i <= n; i++)
            inp << a[i] << " ";
    }
}
