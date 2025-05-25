#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int MAXN = 100;
const int MAXM = 10000;
const int Lim = 1000;
const string ProbName = "P1";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

int n, m;

void Gen1(ofstream& inp) {
    // n <= 100, m <= 200, Wi, Vi, Ai <= 1000
    n = Rand(60, 100);
    m = Rand(100, 200);

    inp << n << " " << m << '\n';
    for (int i = 1; i <= n; i++)
        inp << Rand(1, 100) << " " << Rand(1, 100) << " " << Rand(1, 1000) << '\n';

    inp.close();
}

void Gen2(ofstream& inp) {
    // n <= 100, m <= 10000, Wi, Vi <= 1000, Ai = 2^x
    n = Rand(90, 100);
    m = Rand(9000, 10000);

    inp << n << " " << m << '\n';
    for (int i = 1; i <= n; i++)
        inp << Rand(1, 100) << " " << Rand(1, 100) << " " << (1 << Rand(0, 9)) << '\n';

    inp.close();
}

void Gen3(ofstream& inp) {
    // n <= 100, m <= 10000, Wi, Vi, Ai <= 1000
    n = Rand(90, 100);
    m = Rand(9000, 10000);

    inp << n << " " << m << '\n';
    for (int i = 1; i <= n; i++)
        inp << Rand(1, 100) << " " << Rand(1, 1000) << " " << Rand(1, 1000) << '\n';

    inp.close();
}

int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 15) Gen1(inp);
        else if (Curtest <= 25) Gen2(inp);
        else Gen3(inp);

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
