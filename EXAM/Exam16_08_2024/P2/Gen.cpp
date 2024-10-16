#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int MAXN = 2e5;
const string ProbName = "P2";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

int n, d;
set<int> leaves;

void Gen(ofstream& inp, int LimN) {
    leaves.clear();

    n = Rand(8, LimN);
    d = Rand(2, min(n / 4, 50));

    inp << n << " " << d << '\n';

    leaves.insert(0);
    for (int i = 1; i < n; i++) {

        if (!Rand(0, 30)) {
            auto it = leaves.begin();
            inp << *it << '\n';

            leaves.erase(it);
            leaves.insert(i);
        } else {
            int x = Rand(0, i - 1);
            inp << x << '\n';

            if (leaves.find(x) != leaves.end()) {
                leaves.erase(x);
                leaves.insert(i);
            }
        }
    }

    inp.close();
}

int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        // system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 18);
        else if (Curtest <= 25) Gen(inp, 1500);
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
