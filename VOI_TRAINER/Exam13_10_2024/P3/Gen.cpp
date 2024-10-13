#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int MAXN = 2000;
const string ProbName = "P3";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

void Gen(ofstream& inp, int subNum) {
    int n = Rand(1, MAXN);
    int m = Rand(1, n);
    int mxmv = (subNum == 2 ? 4 * n : 2 * n - 2);
    inp << n << " " << m << " " << mxmv << '\n';
    inp.close();
}


int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 1);
        else if (Curtest <= 20) Gen(inp, 2);
        else Gen(inp, 3);
    }
}