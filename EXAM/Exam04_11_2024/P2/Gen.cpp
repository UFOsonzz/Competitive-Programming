#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int MAXN = 1e5;
const string ProbName = "P2";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

int n, m;

void Gen(ofstream& inp, int limN) {
    n = Rand(6, limN);
    long long limM = min(1LL * n * (n - 1) / 2, 4LL * MAXN);

    m = Rand(n, (int)limM);

    inp << n << " " << m << '\n';

    for (int i = 1; i <= m; i++) {
        int u, v;
        do {
            u = Rand(1, n);
            v = Rand(1, n);
        } while (u == v);

        inp << u << " " << v << '\n';
    }

    inp.close();
}

int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 40);
        else if (Curtest <= 20) Gen(inp, 5000);
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