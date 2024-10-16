#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5;

int n, c, a[MAXN + 5], occ[MAXN + 5];

vector<int> Value_index[MAXN + 5];

int Kadane(vector<int>& arr) {
    int ansmax = 0, curmax = 0;

    for (auto c : arr) {
        if (curmax > 0) curmax += c;
        else curmax = c;
        ansmax = max(ansmax, curmax);
    }

    return ansmax;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> c;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        Value_index[a[i]].push_back(i);

        occ[i] = occ[i - 1];
        if (a[i] == c) occ[i]++;
    }

    int ans = 0;

    for (int i = 1; i <= MAXN; i++) {
        if (Value_index[i].empty() || i == c) continue;
        vector<int> tmp_arr(0);

        for (int j = 0; j < Value_index[i].size(); j++) {
            if (j > 0) tmp_arr.push_back(-(occ[Value_index[i][j]] - occ[Value_index[i][j - 1]]));
            tmp_arr.push_back(1);
        }

        ans = max(ans, Kadane(tmp_arr));
    }

    cout << occ[n] + ans;
}

/*
    occ la mang tien to so lan xuat hien cua gia tri c tu 1 den i
    goi ham get so luong v trong doan l, r la get(l, r, v)
    ans = max(occ[n] + (get(l, r, k) - get(l, r, c)))
    occ[n] co dinh --> cuc dai gia tri get(l, r, k) - get(l, r, c)
    chuyen bai toan ve tim doan con lien tiep co tong lon nhat (kadane)
    (hinh dung moi so k la mot gia tri +1, va xen giua chung la cac gia tri -(so lan xuat hien c o giua))
*/