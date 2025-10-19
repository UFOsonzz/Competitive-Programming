#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const string ProbName = "P4";
const int MAXN = 1e6;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long Rand(long long l, long long r) {
    return l + rng() % (r - l + 1);
}

void Gen(ofstream& inp, int subtask) {
    int lim, n;
    if (subtask == 1)
        lim = 100, n = Rand(1, 100);
    else if (subtask == 2)
        lim = 1000, n = Rand(1, 1000);
    else lim = 5e5, n = Rand(1, 5e5);

    inp << n << " " << Rand(1, lim / 10) << '\n';
    for (int i = 1; i <= n; i++)
        inp << Rand(1, lim) << " ";
    inp.close();
}


int main() {
    
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        //system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 10);
        else if (Curtest <= 20) Gen(inp, 2);
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