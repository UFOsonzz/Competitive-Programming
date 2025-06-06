#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const string ProbName = "FUNNY";

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long Rand(long long l, long long r) {
    return l + rng() % (r - l + 1);
}

void Gen(ofstream& inp, int limT, long long limAB) {
    int t = Rand(1, limT);
    inp << t << " " << Rand(1, 99) << '\n';
    while (t--) {
        long long a = Rand(100, limAB);
        long long b = Rand(a, limAB);
        inp << a << " " << b << '\n';
    }
    inp.close();
}


int main() {
    
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        // system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 25) Gen(inp, 1, 1e6);
        else if (Curtest <= 45) Gen(inp, 1e5, 1e6);
        else Gen(inp, 1e5, 1e18);
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