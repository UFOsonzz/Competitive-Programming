#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const string ProbName = "P2";
const int MAXN = 5e4;
const int MAXV = 1e6;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long Rand(long long l, long long r) {
    return l + rng() % (r - l + 1);
}

void Gen(ofstream& inp, int mx, int spec) {
    int n = Rand(1, mx);
    inp << n << '\n';
    for (int i = 1; i <= n; i++)
        inp << (spec ? Rand(0, 6) : Rand(1, MAXV)) << " ";
    inp.close();
}


int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 20) Gen(inp, 1000, 0);
        else if (Curtest <= 40) Gen(inp, MAXN, 1);
        else Gen(inp, MAXN, 0);
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