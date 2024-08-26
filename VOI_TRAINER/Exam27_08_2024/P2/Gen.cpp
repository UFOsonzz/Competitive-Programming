#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int Testnum = 50;
const int MAXN = 1e6;
const ll MAXK = (1LL << 62) - 1;

const string ProbName = "P2";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll Rand(ll l, ll r) {
    return l + rng() % (r - l + 1);
}

int n, m, p[MAXN + 5];
ll k, w[MAXN + 5];

void Gen(ofstream& inp, int limN) {
    n = Rand(1, limN);
    k = Rand(1, (ll)n * n);

    inp << n << " " << k << '\n';
    
    ll limK = (limN == 1000 ? 2000 : MAXK);

    for (int i = 1; i < n; i++)
        inp << Rand(1, i) << " " << Rand(0, limK) << '\n';

    inp.close();
}

int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 1000);
        else if (Curtest <= 35) Gen(inp, 1e5);
        else Gen(inp, MAXN);

    }
    system("g++ Sol.cpp -o Sol");
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        string Outname = sub_folder + "\\" + ProbName + ".out";
        ifstream input_file(Inpname);
        if (!input_file) {
            cerr << "Khong tim thay file " << Inpname << '\n';
            continue;
        }
        input_file.close();
        string command = "Sol.exe < " + Inpname + " > " + Outname;
        system(command.c_str());
        cerr << "Finished Test " << Curtest << "!\n";
    }
}
