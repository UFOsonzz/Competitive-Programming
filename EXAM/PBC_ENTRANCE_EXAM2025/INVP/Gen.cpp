#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const string ProbName = "INVP";

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long Rand(long long l, long long r) {
    return l + rng() % (r - l + 1);
}

void Gen(ofstream& inp, int limN, int limK) {
    int n = Rand(1, limN);
    int k = Rand(1, limK);

    inp << n << " " << k << '\n';
    for (int i = 1; i <= n; i++)
        inp << Rand(-1e9, 1e9) << " ";
    inp << '\n';
    for (int i = 1; i <= k; i++)
        inp << Rand(-1e6, 1e6) << " ";
    inp.close();
}


int main() {
    
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 1e2, 1);
        else if (Curtest <= 30) Gen(inp, 1e3, 100);
        else Gen(inp, 1e5, 100);
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