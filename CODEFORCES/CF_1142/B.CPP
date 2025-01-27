#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
const int LG = 20;

int n, m, q, a[MAXN], per[MAXN], pos[MAXN], ap[MAXN], nxt[MAXN][LG], mn[MAXN][LG];

int get_min(int l, int r) {
    int lglr = __lg(r - l + 1);

    return min(mn[l][lglr], mn[r - (1 << lglr) + 1][lglr]);
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++) {
        cin >> per[i];
        pos[per[i]] = i;
    }

    per[0] = per[n];

    for (int i = 1; i <= m; i++)
        cin >> a[i];

    for (int t = 0; t < LG; t++)
        for (int i = 1; i <= m + 1; i++)
            nxt[i][t] = mn[i][t] = m + 1;

    for (int i = m; i >= 1; i--) {
        int nxt_val = per[(pos[a[i]] + 1) % n];
        nxt[i][0] = (ap[nxt_val] != 0 ? ap[nxt_val] : m + 1);
        ap[a[i]] = i;
    }

    for (int t = 1; t < LG; t++) {
        for (int i = 1; i <= m; i++) {
            nxt[i][t] = nxt[nxt[i][t - 1]][t - 1];
        }
    }

    for (int i = 1; i <= m; i++) {
        int pos = i;
        for (int t = LG - 1; t >= 0; t--)
            if ((n - 1) >> t & 1) pos = nxt[pos][t];
        mn[i][0] = pos;
    }

    for (int t = 1; t < LG; t++) {
        for (int i = 1; i + (1 << t) - 1 <= m; i++)
            mn[i][t] = min(mn[i][t - 1], mn[i + (1 << (t - 1))][t - 1]);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        if (get_min(l, r) <= r)
            cout << 1;
        else cout << 0;
    }
}

/*
    coi per[0] = per[n]
    voi moi phan tu trong mang a[], tim mot thang next cua no thoa man: 
    next[i] la thang gan nhat co gia tri = per[(pos[[i]] + 1) % n] (vi tri gan nhat cua so tiep theo trong hoan vi)
    -> viec tim mot subsequence ket thuc som nhat bat dau o vi tri i la viec ta nhay n - 1 lan tren mang next[] -> dung binary lifting de nhay n - 1 lan voi moi phan tu
    -> tim min vi tri phai gan nhat neu day bat dau o vi tri trai la i voi moi phan tu tu l -> r, neu min <= r -> co subsequence
*/