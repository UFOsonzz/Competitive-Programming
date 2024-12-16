#include <bits/stdc++.h> 

using namespace std;

const int MAXN = 2300;
const int MAXM = 3600;
const int add = MAXN >> 1;
const int dx[8] = {2, 1, -2, -1, 2, 1, -2, -1};
const int dy[8] = {1, 2, -1, -2, -1, -2, 1, 2};

int kx, ky, px, py, turn;
int d[MAXN + 5][MAXN + 5];
bool vis[MAXN + 5][MAXN + 5];
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> kx >> ky >> px >> py >> turn;
	
	if (turn) px--;
	
	if ((kx - px + ky - py) % 2 == 0) 
        return cout << "NO", 0;
	
	kx += add; ky += add; 
    px += add; py += add;
	memset(vis, false, sizeof(vis));
	memset(d, 0x3f, sizeof(d));

    queue<pair<int, int>> q;
	q.emplace(kx, ky);

	d[kx][ky] = 0; vis[kx][ky] = true;

	while (!q.empty()) {
		pair<int, int> u = q.front();
        q.pop();

		for (int i = 0; i < 8; i++) {
			int x = dx[i] + u.first;
            int y = dy[i] + u.second;
			x++;

			if (1 <= x && x < MAXN && 1 <= y && y < MAXN) {
				if (!vis[x][y]) {
					vis[x][y] = true;
					d[x][y] = d[u.first][u.second] + 1;
					q.emplace(x, y);

					if (make_pair(x - 1, y) == make_pair(px, py)) 
						return cout << "YES" << '\n' << d[x][y], 0;
				}
			}
		}
	}
}

/*
    Mac dinh la ma di truoc, neu tot di truoc thi cho tot di 1 buoc xong giai bai toan voi ma di truoc
    de ma di truoc thang thi xong moi turn (ca tot ca ma di) thi chenh tong chenh lech manhattan phai le
        ly do : gia su co thoi diem ma di truoc va an duoc tot, neu luc do tot di chuyen 1 buoc sau khi bi an thi chenh lech se la 1
        -> o turn cuoi cung thi chenh lech la so le 
        mat khac, sau moi turn thi tinh chan le cua chenh lech manhattan khong doi vi mot ben +2 +1, mot ben +1 => +/- 2 -> ko doi tinh chan le
        => dieu kien dau tien la tong chenh lech manhattan phai chan
    sau khi kiem tra chenh lech manhattan chan xong, ta chi can tim duong di ngan nhat tu o goc den o x, y
     * trick : cu moi lan di chuyen tu x1, y1 den trang thai x2, y2, thi thay vi di den do ta se di den x2 + 1, y2. 
    Lam nhu vay thi khi den o x, y sau t buoc, thuc chat la ta da den o (x - t, y) sau t buoc, cung chinh la o cua con tot sau t buoc
*/