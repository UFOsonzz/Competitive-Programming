#include <bits/stdc++.h>
using namespace std;
using Answer = tuple<int, int, int>;

const int MAXN = 3000;

string s, t;

int pi1[2 * MAXN + 5], pi2[2 * MAXN + 5];

Answer Res = {0, 0, 0};

void Calc(string st, int *pi) {
    pi[0] = 0;

    for (int i = 1; i < (int)st.size(); i++) {
        int cur = pi[i - 1];

        while (st[i] != st[cur] && cur > 0)
            cur = pi[cur - 1];

        if (st[i] == st[cur]) cur++;
        pi[i] = cur;
    }
}

void Solve(bool Rev) {
    int n = (int)s.size();
    int m = (int)t.size();

    for (int i = 0; i < n; i++) {
        // Split : [0, i - 1](reverse) + [i, |s| - 1]

        string s1 = s.substr(0, i);
        string s2 = s.substr(i, n - i);

        reverse(s1.begin(), s1.end());
        Calc(s1 + '#' + t, pi1);
        
        reverse(t.begin(), t.end());
        Calc(s2 + '#' + t, pi2);
        reverse(t.begin(), t.end());

        for (int j = 1; j <= m; j++)
		    Res = max(Res, {pi1[i + j] + pi2[n + m - i - j], i - pi1[i + j],
			          Rev ? m - j - pi2[n + m - i - j] : j - pi1[i + j]});
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> s >> t;

    Solve(false);
    reverse(t.begin(), t.end());
    Solve(true);

    int l, u, v;
    tie(l, u, v) = Res;

    cout << l << "\n" << u << " " << v;
}

/*
    substring ben S se co dang A + B, substring ben T se co dang B + A
    De kiem tra thi ta for vach ngan A, B ben xau S, sA : [0, i - 1], sB : [i, |S| - 1]
    Ta reverse sA roi ghep no voi xau reverse T
    Ta ghep sB voi xau T
    --> KMP voi cac xau vua ghep se ra duoc do dai lon nhat
    ** Luu y co the lat nguoc xau vi du abcd == dcba
*/