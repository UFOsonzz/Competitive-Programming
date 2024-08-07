#include <bits/stdc++.h>
using namespace std;
const int Limit = 5e4;
int n, ElsieDeck[Limit + 5], MaxPre[Limit + 5], MaxSuf[Limit + 5];
set<int> BessieDeck;
void Calculate(int MaxAns[], bool HighCardWin) {
    BessieDeck.clear();
    for (int i = 1; i <= 2 * n; i++)
        BessieDeck.insert(i);
    for (int i = 1; i <= n; i++)
        BessieDeck.erase(ElsieDeck[i]);
    MaxAns[0] = 0;
    for (int i = 1; i <= n; i++) {
        MaxAns[i] = MaxAns[i - 1];
        if (HighCardWin == true) {
            auto it = BessieDeck.upper_bound(ElsieDeck[i]);
            if (it != BessieDeck.end()) {
                MaxAns[i]++;
                BessieDeck.erase(it);
            }
        } else {
            auto it = BessieDeck.upper_bound(ElsieDeck[i]);
            if (it != BessieDeck.begin()) {
                MaxAns[i]++;
                BessieDeck.erase(--it);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> ElsieDeck[i];
    Calculate(MaxPre, true);
    reverse(ElsieDeck + 1, ElsieDeck + 1 + n);
    Calculate(MaxSuf, false);
    int ans = 0;
    for (int i = 0; i <= n; i++) 
        ans = max(ans, MaxPre[i] + MaxSuf[n - i]);
    cout << ans;
}
/*
    Chien thuat choi neu chi co highcardwin
    tai moi vi tri ta se chon thang nho nhat co the thoa man > elsiedeck[i]
    Chien thuat choi neu chi co lowcardwin
    tai moi vi tri ta se chon thang lon nhat thoa man < elsiedeck[i]
    Ta co the giai quyet bai toan voi prefix(highcardwin) va suffix(lowcardwin) rieng roi cong lai lay max, giai thich : 
    Neu nhu cach chon prefix va suffix xung dot voi nhau, nghia la co mot card duoc su dung 2 lan --> se co card khong duoc su dung lan nao
    neu card ko dc su dung < card dung 2 lan thi ta se dung no thay cho card 2 lan o phan suffix, va nguoc lai thi ta thay o phan prefix
*/