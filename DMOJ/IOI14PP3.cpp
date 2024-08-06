#include <bits/stdc++.h>
using namespace std;
const int LimN = 8;
int n, x, y;
void Place(int Centerx, int Centery, int dir) {
    switch (dir) {
        case 0 : {
            // L binh thuong
            cout << Centerx << " " << Centery << " " << Centerx - 1 << " " << Centery << " " << Centerx << " " << Centery + 1 << '\n';
            break;
        }
        case 1 : {
            // xoay 90 clockwise
            cout << Centerx << " " << Centery << " " << Centerx << " " << Centery + 1 << " " << Centerx + 1 << " " << Centery << '\n';
            break;
        }
        case 2 : {
            // xoay 180 clockwise
            cout << Centerx << " " << Centery << " " << Centerx << " " << Centery - 1 << " " << Centerx + 1 << " " << Centery << '\n';
            break;
        }
        case 3 : {
            // xoay 270 clockwise
            cout << Centerx << " " << Centery << " " << Centerx << " " << Centery - 1 << " " << Centerx - 1 << " " << Centery << '\n';
            break;
        }
        default : {
            assert(0);
            break;
        }
    }
}
void RecursivePlacement(int Topleftx, int Toplefty, int Size, int Coveredx, int Coveredy) {
    if (Size == 0) return;
    vector<pair<int, int>> CoveredCoordinate = {
        {Topleftx + (1 << (Size - 1)) - 1, Toplefty + (1 << (Size - 1)) - 1}, 
        {Topleftx + (1 << (Size - 1)) - 1, Toplefty + (1 << (Size - 1))},
        {Topleftx + (1 << (Size - 1)), Toplefty + (1 << (Size - 1))}, 
        {Topleftx + (1 << (Size - 1)), Toplefty + (1 << (Size - 1)) - 1}
    };
    if (Coveredy < Toplefty + (1 << (Size - 1))) {
        // nam ve phia ben trai
        if (Coveredx < Topleftx + (1 << (Size - 1))) {
            // nam ve phia tren ben trai
            Place(Topleftx + (1 << (Size - 1)), Toplefty + (1 << (Size - 1)), 3);
            CoveredCoordinate[0] = {Coveredx, Coveredy};
        } else {
            // nam ve phia duoi ben trai
            Place(Topleftx + (1 << (Size - 1)) - 1, Toplefty + (1 << (Size - 1)), 2);
            CoveredCoordinate[3] = {Coveredx, Coveredy};
        }
    } else {
        // nam ve phia ben phai
        if (Coveredx < Topleftx + (1 << (Size - 1))) {
            // nam ve phia tren ben phai
            Place(Topleftx + (1 << (Size - 1)), Toplefty + (1 << (Size - 1)) - 1, 0);
            CoveredCoordinate[1] = {Coveredx, Coveredy};
        } else {
            // nam ve phia duoi ben phai
            Place(Topleftx + (1 << (Size - 1)) - 1, Toplefty + (1 << (Size - 1)) - 1, 1);
            CoveredCoordinate[2] = {Coveredx, Coveredy};
        }
    }
    RecursivePlacement(Topleftx, Toplefty, Size - 1, CoveredCoordinate[0].first, CoveredCoordinate[0].second);
    RecursivePlacement(Topleftx, Toplefty + (1 << (Size - 1)), Size - 1, CoveredCoordinate[1].first, CoveredCoordinate[1].second);
    RecursivePlacement(Topleftx + (1 << (Size - 1)), Toplefty + (1 << (Size - 1)), Size - 1, CoveredCoordinate[2].first, CoveredCoordinate[2].second);
    RecursivePlacement(Topleftx + (1 << (Size - 1)), Toplefty, Size - 1, CoveredCoordinate[3].first, CoveredCoordinate[3].second);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> x >> y;
    RecursivePlacement(0, 0, n, x, y);

}