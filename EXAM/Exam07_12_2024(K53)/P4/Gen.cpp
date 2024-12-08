#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const string ProbName = "P4";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

void Gen(ofstream& inp, int MAXN) {
    int n = Rand(1, MAXN);
    int m = min(Rand(1, 5000), n * (n - 1) / 4);

    inp << n << " " << m << '\n';

    map<pair<int, int>, bool> Existed;

    for (int i = 1; i <= m; i++) {
        int u, v;
        do {
            u = Rand(1, n);
            v = Rand(1, n);
        } while (u == v || Existed.find(make_pair(u, v)) != Existed.end() || Existed.find(make_pair(v, u)) != Existed.end());
        inp << u << " " << v << '\n';
        Existed[make_pair(u, v)] = true;
    }
    
    inp.close();
}


int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 20) Gen(inp, 500);
        else Gen(inp, 2500);

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