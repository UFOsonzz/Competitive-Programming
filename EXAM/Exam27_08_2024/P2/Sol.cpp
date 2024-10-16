#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define fi first
#define se second

const int MAXN = 1e6;
const int LG = 62;

int n, CurLevelcnt, p[MAXN + 5], CurLevel[MAXN + 5][2], Trie1[MAXN + 5], Trie2[MAXN + 5], SubtreeSize[MAXN + 5];
ll k, w[MAXN + 5];
// Trie1 la phan tu w[i] dang o dau trong trie thu nhat
// Trie2 la vi tri cua partner cua w[i] trong Trie2, neu partner khong ton tai thi = 0
// Trie1 va Trie2 co hinh dang giong nhau nhung cac node duoc xet o 2 trie nay khac nhau

void Reset() {
    for (int i = 1; i <= CurLevelcnt; i++) 
        CurLevel[i][0] = CurLevel[i][1] = SubtreeSize[i] = 0;
    
    CurLevelcnt = 0;
}

int GetId(int Node, int Bit) {
    if (CurLevel[Node][Bit] == 0) CurLevel[Node][Bit] = ++CurLevelcnt;
    return CurLevel[Node][Bit];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 2; i <= n; i++) {
        cin >> p[i] >> w[i];
        w[i] ^= w[p[i]];
    }

    // Root Level
    for (int i = 1; i <= n; i++)
        Trie1[i] = Trie2[i] = 1;

    ll Ans = 0;
    for (int t = LG; t >= 0; t--) {
        Reset(); // Reset
        // Init Level t cua Trie1
        for (int i = 1; i <= n; i++) {
            Trie1[i] = GetId(Trie1[i], (w[i] >> t) & 1);
            SubtreeSize[Trie1[i]]++;
        }

        // Tinh tong so cap di theo pattern hien tai va co bit t = 0
        ll Left_Total = 0;
        for (int i = 1; i <= n; i++) 
            Left_Total += SubtreeSize[CurLevel[Trie2[i]][(w[i] >> t) & 1]];

        // Neu Left_Total ko du k --> Ans co bit thu t bat
        int CurLevelBit = 0;
        if (Left_Total < k) {
            k -= Left_Total;
            CurLevelBit = 1;
            Ans += (1LL << t);
        }

        // Init Level t cua Trie2 (cac partner)
        for (int i = 1; i <= n; i++) 
            Trie2[i] = CurLevel[Trie2[i]][CurLevelBit ^ ((w[i] >> t) & 1)];
        
    }    

    cout << Ans;
}
/*
    Duyet cac bit theo thu tu tu cao -> thap
    Dem xem co bao nhau cap w[i] ^ w[j] co bit t bat/tat bang trie
    ** Toi uu trie : ** 
    Gia su ket qua hien tai khi duyet den bit t la Ans 
    Voi moi w[i] ta duy tri vi tri cua partner cua w[i] tren trie thoa man w[i] ^ partner = Ans (chi tinh cac bit da duyet)
    Tuong tuong viec ta duyet cac bit giong nhu bfs tung level cua trie 
    --> Tai moi thoi diem duyet bit t ta chi quan tam den level cua bit t ma khong quan tam den cac level o tren --> ko phai luu toan bo trie
    Khoi tao hai mang Trie1[i] va Trie2[i] lan luot la vi tri w[i] va vi tri cua partner w[i] trong trie hien tai
    Luc vua duyet den level t ta danh so lai cac node o level t tren trie bat dau tu 1
    Duy tri mang SubtreeSize[i] de dem xem co bao nhieu w[] o trong cay con cua node i
    Tinh xem co bao nhieu cap di theo pattern hien tai co bit t = 0 bang mang SubtreeSize[] (Trie2[i] == 0 ko anh huong vi cac node trong trie cua ta danh so tu 1)
    Sau khi tinh toan xong o level t thi cap nhat lai Trie2 (cap nhat lai cho cac partner)
*/