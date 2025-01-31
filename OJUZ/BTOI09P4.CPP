#include <bits/stdc++.h>

using namespace std;
using dt = long double;

const int MAXN = 1505;

int n;
pair<dt, dt> pt[MAXN];

map<pair<pair<dt, dt>, dt>, vector<pair<int, int>>> Center;

dt Area(int a, int b, int e, int f) {
    pair<dt, dt> vec_ae = {pt[e].first - pt[a].first, pt[e].second - pt[a].second};
    pair<dt, dt> vec_af = {pt[f].first - pt[a].first, pt[f].second - pt[a].second};

    return abs(vec_ae.first * vec_af.second - vec_ae.second * vec_af.first);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> pt[i].first >> pt[i].second;

    dt ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            pair<dt, dt> Cen = {(pt[i].first + pt[j].first) / 2, (pt[i].second + pt[j].second) / 2};
            dt len = hypot(Cen.first - pt[i].first, Cen.second - pt[i].second);
            pair<pair<dt, dt>, dt> Cen_len = {Cen, len};
            Center[Cen_len].emplace_back(i, j);
        }
    }

    for (auto c : Center) {
        for (int i = 0; i < c.second.size(); i++) {
            for (int j = 0; j < i; j++) {
                int a = c.second[i].first;
                int b = c.second[i].second;
                int e = c.second[j].first;
                int f = c.second[j].second;
                
                ans = max(ans, Area(a, b, e, f));
            }
        }
    }

    cout << fixed << setprecision(0) << ans;
}

/*
    do phuc tap bai nay co armotized (khong ro la bao nhieu)
    co the tinh toan o muc (n/2) ^ 3 / big_constant

    voi moi cap diem thi chung tao thanh mot doan thang, doan thang do duoc dac trung boi trung diem va do dai doan do
    2 duong thang tao thanh 2 duong cheo cua hcn phai thoa man co cung trung diem va cung do dai
    voi moi cap (trung diem, do dai) ta luu 1 vector, sau do for cac cap duong thang trong moi vector va tinh kq

    (optional) co the toi uu thanh dpt chuan hon bang cach voi moi vector ta sort cac duong thang sao cho chung theo thu tu vong tron
    sau do two pointer : voi moi doan thang tim thang tao voi no mot goc gan 90 do nhat -> dien tich lon nhat
*/