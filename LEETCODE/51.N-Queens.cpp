class Solution {
public:
    int n, cnt;
    bool a[10][10];
    vector<vector<string>> solutions;
    bool check(int r, int c) {
        for (int i = 1; i < c; i++)
            if (a[r][i]) return false;
        for (int i = 1; i < r; i++)
            if (a[i][c]) return false;
        int i = r, j = c;
        while (i > 0 && j > 0) {
            if (a[i][j]) return false;
            --i; --j;
        }
        i = r; j = c;
        while (i > 0 && j <= n) {
            if (a[i][j]) return false;
            --i; ++j;
        }
        return true;
    }
    void trying(int r, int c) {
        if (r > n) {
            if (cnt < n) return;
            vector<string> rep;
            for (int i = 1; i <= n; i++) {
                string sol = "";
                for (int j = 1; j <= n; j++) {
                    if (a[i][j]) sol += 'Q';
                    else sol += '.';
                    if (j == n) rep.push_back(sol);
                }
            }
            solutions.push_back(rep);
            return;
        }
        int newr = (r + (c == n)), newc = (c == n ? 1 : c + 1);
        if (check(r, c)) {
            a[r][c] = 1;
            ++cnt;
            trying(newr, newc);
            --cnt;
        }

        a[r][c] = 0;
        trying(newr, newc);
    }

    vector<vector<string>> solveNQueens(int inpp) {
        n = inpp;
        trying(1, 1);
        return solutions;
    }
};
