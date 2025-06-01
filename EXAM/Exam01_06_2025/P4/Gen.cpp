#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const string ProbName = "P4";
const int MAXN = 1000;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long Rand(long long l, long long r) {
    return l + rng() % (r - l + 1);
}

void Gen(ofstream& inp, int subtask) {
    int n = Rand(1, 1000), k = (subtask == 2 ? Rand(1, 3000) : Rand(1, 1e8));
    inp << n << " " << k << '\n';
    int cstw = Rand(1, 1e8);
    for (int i = 1; i <= n; i++) {
        if (subtask == 1)
            inp << cstw << " ";
        else if (subtask == 2)
            inp << Rand(1, 1000) << " ";
        else inp << Rand(1, 1e8) << " ";
    }

    inp.close();
}

int main() {
    
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 15) Gen(inp, 1);
        else if (Curtest <= 25) Gen(inp, 2);
        else Gen(inp, 3);
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