#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int MAXN = 2e5;
const int MAXM = 1e9;

const string ProbName = "P1";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

int n, m, a[MAXN + 5];

void Gen(ofstream& inp, int limN, int limM) {
    n = Rand(1, limN);
    m = Rand(1, limM);

    inp << n << " " << m << '\n';

    for (int i = 1; i <= n; i++)
        inp << Rand(1, m) << " ";

    inp.close();
}

int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 15) Gen(inp, 500, 500);
        else if (Curtest <= 35) Gen(inp, 5000, 5000);
        else Gen(inp, MAXN, MAXM);

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
