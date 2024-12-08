#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const string ProbName = "P6";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

void Gen(ofstream& inp, int MAXN) {
    int n = Rand(1, MAXN);  
    int q = Rand(1, MAXN);

    inp << n << '\n';

    for (int i = 2; i <= n; i++) {
        inp << Rand(1, i - 1) << " " << i << '\n';
    }    

    inp << q << '\n';

    while (q--) {
        int u = Rand(1, n);
        int v = Rand(1, n);
        int r = Rand(1, n);

        inp << r << " " << u << " " << v << '\n';
    }

    inp.close();
}


int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 100);
        else if (Curtest <= 30) Gen(inp, 1e5);
        else Gen(inp, 2e5);

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