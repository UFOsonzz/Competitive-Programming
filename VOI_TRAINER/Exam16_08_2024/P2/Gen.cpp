#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int MAXN = 2e5;

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
        
        if (!Rand(0, 4)) {
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
        string Testname = "test" + to_string(Curtest) + ".inp";

        ofstream inp(Testname);
        if (Curtest <= 10) Gen(inp, 18);
        else if (Curtest <= 25) Gen(inp, 1500);
        else Gen(inp, MAXN); 

    }
    system("g++ Sol.cpp -o Sol");
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string Inpname = "test" + to_string(Curtest) + ".inp";
        string Outname = "test" + to_string(Curtest) + ".out";
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