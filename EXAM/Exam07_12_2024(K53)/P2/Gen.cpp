#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int N = 2e5;
const string ProbName = "P2";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

char a[N + 5];

void Gen(ofstream& inp, int MAXN) {
    int TestNum = Rand(1, 15);
    inp << TestNum << '\n';
    while (TestNum--) {
        int len = Rand(1, MAXN);
        for (int i = 0; i < len; i++)
            a[i] = (char)('a' + Rand(0, 25));

        for (int i = 0; i < len; i++)
            inp << a[i];
        inp << '\n';

        vector<int> rnd(len);
        iota(rnd.begin(), rnd.end(), 0);

        int q = min(Rand(1, MAXN / 2), len);

        inp << q << '\n';
        while (q--) {
            inp << Rand(1, 2) << " " << rnd.back() << '\n';
            rnd.pop_back();
        }
    }
    
    inp.close();
}


int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 20) Gen(inp, 20000);
        else Gen(inp, N);

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