#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int l, r, idx;
    Interval() {}
    Interval(int l, int r, int idx) :
        l(l), r(r), idx(idx) {}
    bool operator < (const Interval& other) const {
        return r < other.r;
    }
};

const int MAXN = 2e5;
const int LG = 18;
const int INF = 1e9;

int n, nxt[MAXN + 5][LG], Compressedidx[MAXN + 5];
Interval Event[MAXN + 5];

int MaxEventNum(int l, int r) {
    // so su kien to chuc duoc nhieu nhat sau ma su kien dau la l su kien cuoi la r (l, r sau khi da sort mang Event) (khong tinh su kien l, r)
    if (Event[l].r >= Event[r].l) return -INF;
    int ans = 0;
    for (int i = LG - 1; i >= 0; i--) {
        if (Event[nxt[l][i]].r < Event[r].l) {
            ans += 1 << i;
            l = nxt[l][i];
        }
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> Event[i].l >> Event[i].r;
        Event[i].idx = i;
    }
    Event[0] = {0, 0, 0};
    Event[n + 1] = {INF, INF, n + 1};
    sort(Event + 1, Event + 1 + n);
    for (int i = 1; i <= n; i++)
        Compressedidx[Event[i].idx] = i;
    for (int i = 0; i < LG; i++) 
        nxt[n + 1][i] = n + 1;

    for (int i = 0, j = 0; i <= n; i++) {
        while (Event[j].l <= Event[i].r) ++j;
        nxt[i][0] = j;
    }
    for (int t = 1; t < LG; t++) {
        for (int i = 0; i <= n; i++) {
            nxt[i][t] = nxt[nxt[i][t - 1]][t - 1];
        }
    }
    set<int> Lexi({0, n + 1});
    cout << MaxEventNum(0, n + 1) << '\n';
    for (int i = 1; i <= n; i++) {
        auto it = Lexi.upper_bound(Compressedidx[i]);
        if (MaxEventNum(*prev(it), Compressedidx[i]) + MaxEventNum(Compressedidx[i], *it) + 1 == MaxEventNum(*prev(it), *it)) 
            cout << i << " ", Lexi.insert(Compressedidx[i]);
    }
}
/*
    Ta luon chon Event tiep theo co r min nhat thoa man l > r cua Event hien tai
    Sap xep cac su kien theo r --> Mot cach chon cac su kien thoa man se luon phai la mot cach chon cac su kien co chi so tang dan (cua mang Event sau khi sap xep theo r)
    Voi moi thang ta tim thang tiep theo ma no se nhay den (tim bang two pointer)
    Sau do tao mang nhay log nxt[i][t] voi y nghia neu hien tai o thang i ma nhay them 2^t buoc thi se den duoc thang nao
    Them cac su kien Event[0] = {0, 0} va Event[n + 1] = {INF, INF} cho de lam vi kieu gi cung co the chon Event[0] o dau va Event[n + 1] o cuoi
    Lay ket qua cua bai toan bang cach nhay log tu Event[0]
    --Tim thu tu tu dien nho nhat bang cach: 
    Tao mot set cac phan tu cua cach chon co thu tu tu dien nho nhat, them san su kien 0 va su kien n + 1 vao
    Sau do xet lan luot cac chi so sau khi sap xep cua cac chi so goc i = 1, 2, ..., n
    Gia su sau khi them no vao set thi no (gia su no la cur) dung ngay sau su kien x va ngay truoc su kien y 
    Mot thang thuoc vao cach chon co thu tu tu dien nho nhat khi va chi khi (Nhay log tu x -> cur + Nhay log tu cur -> y) + 1 = Nhay log tu x -> y
    Neu cur thoa man dang thuc tren thi ta them cur vao set, khong thi thoi.
*/