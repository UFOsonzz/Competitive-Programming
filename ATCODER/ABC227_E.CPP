#include <bits/stdc++.h>

using namespace std;

const string KEY = "KEY";

map<string, map<int, long long>> dp;

long long Calc(string s, int k) {
    if (k < 0) return 0;
    if ((int)s.size() == 1) return 1;
    if (dp[s].find(k) != dp[s].end()) return dp[s][k];

    long long sum = 0;
    for (auto& c : KEY) 
        for (int i = 0; i < s.size(); i++) 
            if (c == s[i]) {
                sum += Calc(s.substr(0, i) + s.substr(i + 1), k - i);
                break;
            }

    return dp[s][k] = sum;
}

int main() {
    string s;
    int k;

    cin >> s >> k;

    cout << Calc(s, k);
}

/*
    mac du maxlen(s) = 30 nhung s chi gom 3 ki tu K, E, Y
    => so xau toi da co the sinh ra sau cac phep swap = C(3, 7) * C(10, 20) = xap xi 5e6 (uoc luong)
        (tren thuc te so xau it hon) 
    => quay lui, de chuyen trang thai trong dpt hop ly thi ta chi xet viec dua ki tu K/E/Y len dau 
        => chuyen trang thai trong dpt O(n) 
*/
