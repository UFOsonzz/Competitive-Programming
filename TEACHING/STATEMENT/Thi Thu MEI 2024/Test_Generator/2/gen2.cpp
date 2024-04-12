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

void gen() {
    int cur = 0;
    for (int i = 1; i <= l; i++)
        a[i] = '.';
    for (int i = l - 2*n; i >= 1; i--) {
        emp[get(0, 2*n)]++;
    }
    int pos = 0;
    for (int i = 0; i < 2*n; i++) {
        pos += emp[i] + 1;
        if (i & 1) a[pos] = 'D';
        else a[pos] = 'T';
    }
}
int main() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    for (int i = 50; i <= 50; i++) {
        string cur_name = "TD" + to_string(i) + ".inp";
        ofstream inp(cur_name);
        int cur = 1e6;
        if (i <= 20) n = 1;
        else if (i <= 40) n = 2;
        int t = get(1, 20);
        inp << t << '\n';
        for (int g = 1; g <= t; g++) {
            l = get(2, cur - 2*(t-g));
            if (i >= 41) n = get(1, max(1, l/10));
            cur -= l;
            inp << l << " " << n << '\n';
            gen();

            for (int j = 1; j <= l; j++)
                inp << a[j];
            inp << '\n';
        }
    }
}
