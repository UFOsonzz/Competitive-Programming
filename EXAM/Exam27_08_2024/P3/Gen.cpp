#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int Testnum = 50;
const int MAXN = 2e5;
const int MAXV = 1e7;

const string ProbName = "P3";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

int n, a[MAXN + 5];

void Gen(ofstream& inp, int limN) {
    n = Rand(1, limN);

    inp << n << '\n';

    int limV = (limN == 500 ? 2000 : MAXV);

    for (int i = 1; i <= n; i++)
        inp << Rand(1, limV) << " ";

    inp.close();
}

int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 500);
        else if (Curtest <= 25) Gen(inp, 1e4);
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
