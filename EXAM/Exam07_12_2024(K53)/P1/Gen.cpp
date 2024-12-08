#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const string ProbName = "P1";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

void Gen(ofstream& inp, int MAXN) {
    int n = Rand(1, (int)sqrt(MAXN));
    int m = Rand(1, MAXN / n);

    inp << n << " " << m << '\n';

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            inp << (char)('a' + Rand(0, 25));
        }
        
        inp << '\n';
    }
    inp.close();
}


int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 20) Gen(inp, 1e3);
        else Gen(inp, 1e5);

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