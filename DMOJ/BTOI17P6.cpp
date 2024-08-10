#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;

class CentroidDecomposition {
    public: 
        const int INFDistance = 1e9;

        int n, *Subtree_Size, *Nearest_SetChild, *CentroidPar;
        vector<int>* adj;
        bool* Selected;
        unordered_map<int, int>* OriginalDistance;
    
        CentroidDecomposition(int Size, int p[]) : 
            Subtree_Size(new int[MAXN + 5]), 
            Nearest_SetChild(new int[MAXN + 5]),
            Selected(new bool[MAXN + 5]),
            adj(new vector<int>[MAXN + 5]),
            CentroidPar(new int[MAXN + 5]),
            OriginalDistance(new unordered_map<int, int>[MAXN + 5]) {

            n = Size;
            for (int i = 1; i < n; i++) {
                adj[p[i]].push_back(i);
                adj[i].push_back(p[i]);
            }

            for (int i = 0; i < n; i++) {
                Selected[i] = false;
                CentroidPar[i] = -1;
                Nearest_SetChild[i] = INFDistance;
            }
        }

        int Dfs_GetSize(int pa, int u) {
            Subtree_Size[u] = 1;
            for (auto& c: adj[u]) {
                if (c == pa || Selected[c]) continue;
                Subtree_Size[u] += Dfs_GetSize(u, c);
            }

            return Subtree_Size[u];
        }

        int Get_Centroid(int pa, int u, int Total_Size) {
            for (auto& c: adj[u]) {
                if (c == pa || Selected[c]) continue;
                if (2 * Subtree_Size[c] > Total_Size)
                    return Get_Centroid(u, c, Total_Size);
            }

            return u;
        }


        void InitDistance(int pa, int u, int Root, int Dis) {
            OriginalDistance[Root][u] = Dis;
            for (auto& c: adj[u]) {
                if (c == pa || Selected[c]) continue;
                InitDistance(u, c, Root, Dis + 1);
            }
        }

        void BuildCentroid(int PrevCentroid, int u) {
            int Total_Size = Dfs_GetSize(0, u);
            int Centroid = Get_Centroid(0, u, Total_Size);

            InitDistance(-1, Centroid, Centroid, 0);
            Selected[Centroid] = true;
            CentroidPar[Centroid] = PrevCentroid;
            
            for (auto& c: adj[Centroid]) 
                if (Selected[c] == false) BuildCentroid(Centroid, c);
        }

        void SetNode(int u) {
            int Temp = u;
            while (Temp != -1) {
                Nearest_SetChild[Temp] = min(Nearest_SetChild[Temp], OriginalDistance[Temp][u]);
                Temp = CentroidPar[Temp];
            }
        }

        bool CheckPlacement(int u, int d) {
            int Temp = u;
            while (Temp != -1) {
                if (Nearest_SetChild[Temp] + OriginalDistance[Temp][u] < d) 
                    return false;
                Temp = CentroidPar[Temp];
            }

            SetNode(u);
            return true;
        }
};

int n, d, p[MAXN + 5], Depth[MAXN + 5];
vector<int> SetOrder;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> d;
    SetOrder.push_back(0);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        Depth[i] = Depth[p[i]] + 1;
        SetOrder.push_back(i);
    }

    sort(SetOrder.begin(), SetOrder.end(), [&](int x, int y) {
        return Depth[x] > Depth[y];
    });

    int Ans = 0;
    CentroidDecomposition Cen(n, p);
    Cen.BuildCentroid(-1, 0);

    for (auto& c: SetOrder)
        Ans += Cen.CheckPlacement(c, d);

    cout << Ans;
}
/*
    Tham lam chon tu duoi len (tu la len goc), moi lan dat mot node thi kiem tra co duoc hay khong bang centroid (giong bai Xenia and Tree)
*/