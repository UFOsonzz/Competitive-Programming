#include <bits/stdc++.h>
using namespace std;
const int Testnum = 50;
const int Limit1 = 2000;
const int Limit2 = 10000;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}
int n, x, y, A[Limit1+5], B[Limit2+5];
void Gen1(ofstream& inp) {
    n = Rand(100, 200);
    x = Rand(1, 500);
    y = Rand(1, 500);
    inp << n << " " << x << " " << y << '\n';
    for (int i = 1; i <= n; i++) {
        A[i] = Rand(1, 30);
        B[i] = Rand(1, 30);
        inp << A[i] << " " << B[i] << '\n';
    }
    inp.close();
}
void Gen2(ofstream& inp) {
    n = Rand(1000, 2000);
    x = Rand(1, 10000);
    y = Rand(1, 10000);
    inp << n << " " << x << " " << y << '\n';
    for (int i = 1; i <= n; i++) {
        A[i] = B[i] = Rand(1, 100);
        inp << A[i] << " " << B[i] << '\n';
    }
    inp.close();
}
void Gen3(ofstream& inp) {
    n = Rand(1000, 2000);
    x = Rand(1, 10000);
    y = Rand(1, 10000);
    inp << n << " " << x << " " << y << '\n';
    int ConstB = Rand(1, 100);
    for (int i = 1; i <= n; i++) {
        A[i] = Rand(1, 100);
        B[i] = ConstB;
        inp << A[i] << " " << B[i] << '\n';
    }
    inp.close();
}
void Gen4(ofstream& inp) {
    n = Rand(1000, 2000);
    x = Rand(1, 10000);
    y = Rand(1, 10000);
    inp << n << " " << x << " " << y << '\n';
    for (int i = 1; i <= n; i++) {
        A[i] = Rand(1, 100);
        B[i] = Rand(1, 100);
        inp << A[i] << " " << B[i] << '\n';
    }
    inp.close();
}
int main() {
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string Testname = "test" + to_string(Curtest) + ".inp";
        ofstream inp(Testname);
        if (Curtest <= 10) Gen1(inp);
        else if (Curtest <= 15) Gen2(inp);
        else if (Curtest <= 20) Gen3(inp);
        else Gen4(inp);
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