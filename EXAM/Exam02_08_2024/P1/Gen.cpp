#include <bits/stdc++.h>
using namespace std;
const int Testnum = 50;
const int Limit = 5e5;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

int n, A[Limit+5], B[Limit+5];
void Gen1(ofstream& inp) {
    n = Rand(1, 20000);
    for (int i = 1; i <= n; i++) {
        A[i] = Rand(-1e9, 1e9);
        B[i] = Rand(-1e9, 1e9);
    }
    inp << n << '\n';
    for (int i = 1; i <= n; i++) 
        inp << A[i] << " ";
    inp << '\n';
    for (int i = 1; i <= n; i++) 
        inp << B[i] << " ";
    inp.close();
}

void Gen2(ofstream& inp) {
    n = Rand(1, Limit);
    for (int i = 1; i <= n; i++) {
        A[i] = Rand(-1e9, 1e9);
        B[i] = Rand(-1e9, 1e9);
    }
    inp << n << '\n';
    for (int i = 1; i <= n; i++) 
        inp << A[i] << " ";
    inp << '\n';
    for (int i = 1; i <= n; i++) 
        inp << B[i] << " ";
    inp.close();
}

int main() {
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string Testname = "test" + to_string(Curtest) + ".inp";
        // 25 sub 1 : n <= 20000 -> trick lor
        // 25 sub 2 : n <= 5e5 -> thuat chuan
        ofstream inp(Testname);
        if (Curtest <= 25) 
            Gen1(inp);
        else Gen2(inp);
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