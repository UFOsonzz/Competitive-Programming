#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int l, n;
char a[N];
void solve() {
    cin >> l >> n;
    for (int i = 1; i <= l; i++)
        cin >> a[i];
    auto sub1 = []() {
        int turn = 0, post, posd;
        for (int i = 1; i <= l; i++) {
            if (a[i] == 'T') post = i;
            if (a[i] == 'D') posd = i;
        }
        while (true) {
            if (turn == 0) {
                if (post + 1 != posd) ++post;
                else if (post > 1) --post;
                else break;
            }
            if (turn == 1) {
                if (posd - 1 != post) --posd;
                else if (posd < n) ++posd;
                else break;
            }
            turn = 1 - turn;
        }
        if (turn == 0) cout << "NO\n";
        else cout << "YES\n";
    };

    auto sub2 = []() {
        int wall, turn = 0, post, posd;
        for (int i = 1; i <= l; i++) {
            if (a[i] == 'T') post = i;
            if (a[i] == 'D') { 
                wall = posd = i; 
                break; 
            }
        }
        while (true) {
            if (turn == 0) {
                if (post + 1 != posd) ++post;
                else if (post > 1) --post;
                else break;
            }
            if (turn == 1) {
                if (posd - 1 != post) --posd;
                else if (posd < wall) ++posd;
                else break;
            }
            turn = 1 - turn;
        }
        if (turn == 1) {
            cout << "YES\n";
            return;
        }
        for (int i = wall + 1; i <= l; i++) {
            if (a[i] == 'T') post = i;
            if (a[i] == 'D') posd = i; 
        }
        while (true) {
            if (turn == 0) {
                if (post + 1 != posd) ++post;
                else if (post > wall + 1) --post;
                else break;
            }
            if (turn == 1) {
                if (posd - 1 != post) --posd;
                else if (posd < n) ++posd;
                else break;
            }
            turn = 1 - turn;
        }
        if (turn == 0) cout << "NO\n";
        else cout << "YES\n";
    };
    auto sub3 = []() {
        int post, posd;
        for (int i = 1; i <= l; i++) {
            if (a[i] == 'T') post = i;
            if (a[i] == 'D') {
                posd = i;
                if ((posd - post) % 2 == 0) {
                    cout << "YES\n";
                    return;
                }
            }
        }
        cout << "NO\n";
    };
}
int main() {
    int t;
    cin >> t;
    while (t--) solve();
}