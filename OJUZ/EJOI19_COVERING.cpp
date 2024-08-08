#include <bits/stdc++.h>
using namespace std;
const int Limit = 1e6;
const int LimitVal = 1000;
const int dirx[4] = {-1, 0, 1, 0};
const int diry[4] = {0, 1, 0, -1};
const int Cornerdirx[4] = {-1, 1, 1, -1};
const int Cornerdiry[4] = {1, 1, -1, -1};
int m, n, k;
vector<vector<int>> Grid, Status;
vector<int> Dsu;
bool InGrid(int& i, int& j) {
    return (0 <= i && i < m && 0 <= j && j < n);
}
int Zip(int& i, int& j) {
    return i * n + j;
}
int FindPar(int u) {
    if (u == Dsu[u]) return u;
    return Dsu[u] = FindPar(Dsu[u]);
}
bool Union(int u , int v) {
    u = FindPar(u);
    v = FindPar(v);
    if (u == v) return false;
    Dsu[v] = u;
    return true;
}
vector<pair<int, int>> Component[Limit];
vector<vector<bool>> isVisited;
vector<pair<int, int>> isVisited_RollBack;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> m >> n;
    Grid.resize(m + 1, vector<int>(n + 1));
    Status.resize(m + 1, vector<int>(n + 1));
    Dsu.resize(n * m + 1);
    for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
        cin >> Grid[i][j], Dsu[Zip(i, j)] = Zip(i, j);
    cin >> k;
    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        Status[x][y] = true;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (Status[i][j] == false) continue;
            for (int dir = 0; dir < 4; dir++) {
                pair<int, int> CloseAdj = {i + dirx[dir], j + diry[dir]};
                pair<int, int> FarAdj = {i + 2 * dirx[dir], j + 2 * diry[dir]};
                pair<int, int> CornerAdj = {i + Cornerdirx[dir], j + Cornerdiry[dir]};
                if (InGrid(CloseAdj.first, CloseAdj.second) && Status[CloseAdj.first][CloseAdj.second] == true)
                    Union(Zip(i, j), Zip(CloseAdj.first, CloseAdj.second));
                if (InGrid(FarAdj.first, FarAdj.second) && Status[FarAdj.first][FarAdj.second] == true)
                    Union(Zip(i, j), Zip(FarAdj.first, FarAdj.second));
                if (InGrid(CornerAdj.first, CornerAdj.second) && Status[CornerAdj.first][CornerAdj.second] == true)
                    Union(Zip(i, j), Zip(CornerAdj.first, CornerAdj.second));
            }
        }
    }

    for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
        if (Status[i][j] == true) 
            Component[FindPar(Zip(i, j))].emplace_back(i, j);
    int Ans = 0;
    isVisited.resize(m + 1, vector<bool>(n + 1));
    for (int i = 0; i < n * m; i++) {
        if (Component[i].empty()) continue;
        int CoverNum = 0, MaxSum = 0;

        for (auto& c: Component[i]) {
            MaxSum += Grid[c.first][c.second];
            for (int dir = 0; dir < 4; dir++) {
                int Cx = c.first + dirx[dir];
                int Cy = c.second + diry[dir];
                if (!InGrid(Cx, Cy) || Status[Cx][Cy] == true) continue;
                if (!isVisited[Cx][Cy]) {
                    isVisited[Cx][Cy] = true;
                    isVisited_RollBack.emplace_back(Cx, Cy);
                    CoverNum++;
                }
            }
        }

        if (CoverNum < 3 * (int)Component[i].size()) {
            cout << "No";
            return 0;
        } else if (CoverNum == 3 * (int)Component[i].size()) {
            for (auto& c: isVisited_RollBack)
                MaxSum += Grid[c.first][c.second];
        } else {
            int MinVal = LimitVal;
            
            for (auto& c: isVisited_RollBack) {
                MaxSum += Grid[c.first][c.second];
                MinVal = min(MinVal, Grid[c.first][c.second]);
            }
            MaxSum -= MinVal;
        }
        Ans += MaxSum;
        for (auto& c: isVisited_RollBack)
            isVisited[c.first][c.second] = 0;
        isVisited_RollBack.clear();
    }
    cout << Ans;
}
/*
    2 dinh mau do co khoang cach manhattan <= 2 (chung dinh, chung canh, cach mot o) thi co canh noi den nhau --> tao ra cac vung lien thong
    Voi mot vung lien thong size n: tu moi dinh cua vung lien thong do ta loang ra 4 o xung quanh no tao thanh hinh chu thap
    cac o duoc loang ra (khong tinh cac dinh mau do) tu cac dinh trong cung mot thanh phan lien thong tao thanh "vung phu song"
    Nhan xet size vung phu song <= 4 * n - (n - 1) boi vi 2 moi dinh loang ra 4 o xung quanh nhung 2 dinh ke nhau thi lai an bot cua nhau 1 o 
    ma 1 thanh phan lien thong thi co it nhat la n - 1 canh --> size vung phu song <= 4 * n - (n - 1) = 3 * n + 1
    Lai co nhan xet : De co the dat cac chu T thoa man doi voi cac dinh trong cung mot vung lien thong thi size vung phu song >= 3 * n
    --> neu size vung phu song < 3 * n --> No
        neu size vung phu song = 3 * n --> Co cach de dat cac chu T sao cho cac chu T phu het tat ca cac o cua vung phu song 
        **Cminh** : Cac truong hop co vung phu song size = 3 * n gom co : 
            Chu trinh cua cac dinh cach nhau 1 o --> truong hop nay de chi ra cach dien
            Dang co mot cay (0 co chu trinh) cac dinh cach nhau 1 o va ta chen them mot dinh chung canh hoac chung dinh vao mot dinh nao do trong cay --> ve cac truong hop ra va ta co the chi ra cach dien
            **Tai sao lai chi co 2 truong hop nay la boi: cu moi lan co 2 dinh chung canh hoac chung dinh thi so o cua vung phu song bi an bot la 2 --> se chi ton tai nhieu nhat 1 cap dinh co chung canh hoac chung dinh
        neu size vung phu song = 3 * n + 1 --> Co cach dat sao cho ta chi bo trong o co gia tri thap nhat trong vung phu song
        **Cminh** : De vung phu song co size = 3 * n + 1 thi vung lien thong bat buoc phai la mot cay
            --> xet va ve hinh cac truong hop ta bo mot trong 4 o cua 
                dinh nam tren duong thang
                dinh nam o goc
            --> du bo bat ki dinh nao thi ta luon xep T de phu kin duoc 3 * n dinh con lai
*/