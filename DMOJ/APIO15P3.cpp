#include <bits/stdc++.h>
using namespace std;
using Citizen = pair<int, int>;
const int LimN = 1e5;
const long long INFDistance = 1e18;
int k, n;
vector<Citizen> CrossingCitizen;
multiset<int> Highheap, Lowheap;
long long Highsum, Lowsum;
long long GetCurrentAnswer(int CitizenNum) {
    long long Median = *(--Lowheap.end());
    // + CitizenNum vi moi lan qua cau mat 1 unit
    return (long long)Lowheap.size() * Median - Lowsum + Highsum - (long long)Highheap.size() * Median + CitizenNum;
}
void HeapRebalancing() {
    // rebalance 2 heap de median luon la *(--Lowheap.end())
    while (Lowheap.size() - 1 > Highheap.size()) {
        auto Temporary = (--Lowheap.end());
        Lowheap.erase(Temporary);
        Lowsum -= *Temporary;
        Highheap.insert(*Temporary);
        Highsum += *Temporary;
    } 
    while (Highheap.size() > Lowheap.size()) {
        auto Temporary = Highheap.begin();
        Highheap.erase(Temporary);
        Highsum -= *Temporary;
        Lowheap.insert(*Temporary);
        Lowsum += *Temporary;
    }
}
void ElementProcessing(int val) {
    // Insert vao 1 trong 2 heap
    if (Lowheap.empty() || val <= *(--Lowheap.end())) {
        Lowheap.insert(val);
        Lowsum += val;
    } else {
        Highheap.insert(val);
        Highsum += val;
    }
}
vector<long long> PrefixProcessing(vector<Citizen>& Vec) {
    // Tra ve ket qua cua bai toan con voi mot tien to cua day Vec
    int sz = Vec.size();
    Highheap.clear();
    Lowheap.clear();
    Highsum = Lowsum = 0;
    vector<long long> resultVec(0);
    for (int i = 0; i < sz; i++) {
        ElementProcessing(Vec[i].first);
        ElementProcessing(Vec[i].second);
        HeapRebalancing();
        resultVec.push_back(GetCurrentAnswer(i + 1));
    }
    return resultVec;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> k >> n;
    long long NonCrossingDistance = 0;
    for (int i = 1; i <= n; i++) {
        char p, q;
        int s, t;
        cin >> p >> s >> q >> t;
        if (p == q) NonCrossingDistance += abs(s - t);
        else CrossingCitizen.emplace_back(s, t);
    }
    long long CrossingDistance = 0;
    
    if (CrossingCitizen.empty() == false) {
        sort(CrossingCitizen.begin(), CrossingCitizen.end(), [&](Citizen X, Citizen Y) {
            // so sanh (s + t) / 2 (diem o giua s va t)
            return (X.first + X.second) < (Y.first + Y.second);
        });
        vector<long long> Prefix = PrefixProcessing(CrossingCitizen);
        reverse(CrossingCitizen.begin(), CrossingCitizen.end());
        vector<long long> Suffix = PrefixProcessing(CrossingCitizen);
    
    
        if (k == 1) CrossingDistance = Prefix[(int)CrossingCitizen.size() - 1];
        else {
            CrossingDistance = INFDistance;
            for (int i = 0; i < (int)CrossingCitizen.size(); i++) {
                // phan ben trai bat dau tu CrossingCitizen[0] -> CrossingCitizen[i]
                if (i < (int)CrossingCitizen.size() - 1) 
                    CrossingDistance = min(CrossingDistance, Prefix[i] + Suffix[(int)CrossingCitizen.size() - 2 - i]);
                else CrossingDistance = min(CrossingDistance, Prefix[i]);
            }
        }
    }
    
    cout << CrossingDistance + NonCrossingDistance;
}