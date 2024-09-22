#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int MAXN = 5e5;
const string ProbName = "P1";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

int n, c, a[MAXN + 5];

void Gen1(ofstream& inp) {
    n = Rand(1, 2000);
    c = Rand(1, MAXN);
    inp << n << " " << c << '\n';
    for (int i = 1; i <= n; i++)
        inp << Rand(1, MAXN) << " ";
    inp.close();
}

void Gen2(ofstream& inp) {
    vector<int> uni(0);

    for (int i = 1; i <= 200; i++)
        uni.push_back(Rand(1, MAXN));
    
    n = Rand(1, MAXN);
    c = uni[Rand(0, 199)];

    inp << n << " " << c << '\n';

    for (int i = 1; i <= n; i++)
        inp << uni[Rand(0, 199)] << " ";
    inp.close();
}

void Gen3(ofstream& inp) {
    n = Rand(1, MAXN);
    c = Rand(1, 2000);
    inp << n << " " << c << '\n';
    for (int i = 1; i <= n; i++)
        inp << Rand(1, 2000) << " ";
    inp.close();
}

int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        //system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen1(inp);
        else if (Curtest <= 20) Gen2(inp);
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