#include <bits/stdc++.h>
using namespace std;
#define inp cout
using ll = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll get(ll x, ll y) {
    return x + rng() % (y - x + 1);
}

const int N = 1e6 + 5;

int l, n, emp[N];
char a[N];
void fix_no() {
    for (int i = 2; i <= 2 * n; i += 2) {
        if (emp[i] & 1) emp[i]--, --l;
    }
}

void gen() {
    for (int i = 1; i <= 2 * n + 1; i++)
        emp[i] = 0;
    int rem = l - 2 * n;
    for (int i = 1; i <= rem; i++) {
        int v = get(1, 2 * n + 1);
        emp[v]++;
    }
    int ans = get(0, 1);
    if (!ans) fix_no();
    int cur = 0;
    for (int i = 1; i <= 2 * n + 1; i++) {
        for (int j = 1; j <= emp[i]; j++) a[++cur] = '.';
        if (i < 2 * n + 1) {
            if (i & 1) a[++cur] = 'T';
            else a[++cur] = 'D';
        }
    }
}



int main() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    for (int i = 1; i <= 50; i++) {
        string cur_name = "TD" + to_string(i) + ".inp";
        ofstream inp(cur_name);
        if (i <= 20) n = 1;
        else if (i <= 40) n = 2;
        int t = get(1, 10);
        inp << t << '\n';
        while (t--) {
            l = get(1, 100000);
            if (i > 40) n = get(1, l / 4);
            gen();
            inp << l << " " << n << '\n';
            for (int j = 1; j <= l; j++) inp << a[j];
            inp << '\n';
        }
    }
}
