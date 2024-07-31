#include <bits/stdc++.h>
using namespace std;
const int Limit = 1e6;
const int Testnum = 50;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}
int n, A[Limit+5];
void Gen1(ofstream& inp) {
    n = Rand(1, 8);
    inp << n << '\n';
    for (int i = 1; i <= n; i++) {
        A[i] = Rand(1, n);
        inp << A[i] << " ";
    }
    inp.close();
}
void Gen2(ofstream& inp) {
    n = Rand(1, Limit);
    inp << n << '\n';
    for (int i = 1; i <= n; i++) {
        A[i] = Rand(1, (i == 1 ? 1 : i - 1));
        inp << A[i] << " ";
    }
    inp.close();
}
void Gen3(ofstream& inp) {
    n = Rand(1, Limit);
    inp << n << '\n';
    for (int i = 1; i <= n; i++) {
        A[i] = Rand(1, n);
        inp << A[i] << " ";
    }
    inp.close();
}
int main() {
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string Testname = "test" + to_string(Curtest) + ".inp";
        ofstream inp(Testname);
        if (Curtest <= 10) Gen1(inp);
        else if (Curtest <= 20) Gen2(inp);
        else Gen3(inp);
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