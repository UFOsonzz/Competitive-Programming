#include <bits/stdc++.h>
using namespace std;
const int LimitNM = 1e5;
const int LimitTrie = 2e6;
const int BUFFER = 1e9;
using Point = pair<int, int>;
int n, m, CharId[2310], QueryAns[LimitNM + 5];
Point RNATrieId[LimitNM + 5], QuerySuffixEuler[LimitNM + 5];
string s[LimitNM + 5];
vector<Point> Axis;
struct Trie {
    int cnt, nxt[LimitTrie][4], Eulercnt, In[LimitTrie], Out[LimitTrie];
    Trie() { cnt = Eulercnt = 0; }
    int TrieAdd(string& x, bool IsRNA) {
        int root = 0;
        for (int i = 0; i < x.size(); i++) {
            if (nxt[root][CharId[x[i]]] == 0)
                if (IsRNA) nxt[root][CharId[x[i]]] = ++cnt;
                else return 0;
            root = nxt[root][CharId[x[i]]];
        }
        return root;
    }
    void dfsEulerTour(int root) {
        In[root] = ++Eulercnt;
        for (int i = 0; i < 4; i++) {
            if (nxt[root][i] == 0)
                continue;
            dfsEulerTour(nxt[root][i]);
        }
        Out[root] = Eulercnt;
    }
} PrefixTrie, SuffixTrie;
int BIT[LimitTrie];
void BITAdd(int pos) {
    while (pos <= SuffixTrie.Eulercnt) {
        BIT[pos]++;
        pos += (pos & (-pos));
    }
}
int BITGetPre(int pos) {
    int Total = 0;
    while (pos > 0) {
        Total += BIT[pos];
        pos -= (pos & (-pos));
    }
    return Total;
}
int BITGetRange(int l, int r) {
    if (l > r) return 0;
    return BITGetPre(r) - BITGetPre(l - 1);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    vector<char> CharList = {'A', 'G', 'C', 'U'};
    for (int i = 0; i < 4; i++) 
        CharId[CharList[i]] = i;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        RNATrieId[i].first = PrefixTrie.TrieAdd(s[i], true);
        reverse(s[i].begin(), s[i].end());
        RNATrieId[i].second = SuffixTrie.TrieAdd(s[i], true);
    }
    PrefixTrie.dfsEulerTour(0);
    SuffixTrie.dfsEulerTour(0);
    for (int i = 1; i <= n; i++) {
        RNATrieId[i].first = PrefixTrie.In[RNATrieId[i].first];
        RNATrieId[i].second = SuffixTrie.In[RNATrieId[i].second];
        Axis.push_back(RNATrieId[i]);
    }
    // s[i] = {prefixid, suffixid}, prefixtrie = {in, out}, suffixtrie = {in, out}
    for (int i = 1; i <= m; i++) {
        string p, q;
        cin >> p >> q;
        Point NonEulerId;
        NonEulerId.first = PrefixTrie.TrieAdd(p, false);
        reverse(q.begin(), q.end());
        NonEulerId.second = SuffixTrie.TrieAdd(q, false);
        if (min(NonEulerId.first, NonEulerId.second) == 0) continue;

        Axis.emplace_back(PrefixTrie.In[NonEulerId.first], -i);
        Axis.emplace_back(PrefixTrie.Out[NonEulerId.first], i + BUFFER);
        QuerySuffixEuler[i] = {SuffixTrie.In[NonEulerId.second], SuffixTrie.Out[NonEulerId.second]};
    }
    sort(Axis.begin(), Axis.end());
    for (auto& c : Axis) {
        if (c.second < 0) {
            QueryAns[-c.second] -= BITGetRange(QuerySuffixEuler[-c.second].first, QuerySuffixEuler[-c.second].second);
        } else if (c.second > BUFFER) {
            QueryAns[c.second - BUFFER] += BITGetRange(QuerySuffixEuler[c.second - BUFFER].first, QuerySuffixEuler[c.second - BUFFER].second);
        } else {
            BITAdd(c.second);
        }
    }
    for (int i = 1; i <= m; i++)
        cout << QueryAns[i] << '\n';
}
/*
    Xay 2 cay Trie: mot cay cho tien to, mot cay cho hau to
    Khoi tao eulertour tren 2 cay trie
    --> Xau i thoa man truy van j khi va chi khi PrefixTrie.in[xau i] thuoc range cay con cua p[i] va SuffixTrie.in[xau i] thuoc range cay con cua q[i]
    --> neu coi {prefixtrie.in[xau i], suffixtrie.in[xau i]} la 1 diem va range cay con cua p[i] va q[i] tao thanh hinh chu nhat 
        (bo qua nhung truy van ma p[i] hoac q[i] khong co trong trie) 
        thi bai toan tro ve dem so diem thuoc hinh chu nhat
    **dem so diem thuoc hinh chu nhat** 
    them diem {prefixtrie.in[xau i], suffixtrie.in[xau i]} (diem loai 3) vao Axis
    them 2 dau cua range cay con cua p[i] vao Axis (dau nho hon loai 1, dau to hon loai 2)
    sap xep axis theo first, neu first = nhau thi sap xep theo uu tien loai 1 roi den loai 3, roi den loai 2
    den diem loai 1 thi ketqua truy van -= tong doan range cay con q[i] (lay bang BIT)
    den diem loai 2 thi ketqua truy van += tong doan range cay con q[i] (lay bang BIT)
    den diem loai 3 thi cong them 1 vao vi tri suffixtrie.in[xau i] trong BIT
*/