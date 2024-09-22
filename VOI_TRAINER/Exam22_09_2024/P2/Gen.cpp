#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int MAXN = 1e5;
const string ProbName = "P2";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

int q;

void Gen(ofstream& inp, int limq) {
    q = Rand(1, limq);

    inp << q << '\n';

    int nodeNum = 0;
    for (int i = 1; i <= q; i++) {
        if (nodeNum == 0) {
            inp << "B " << -1 << '\n';
            nodeNum++;
            continue;
        }
        int qrate = Rand(1, 4);
        if (qrate == 1) inp << "Q " << Rand(1, nodeNum) << '\n';
        else {
            int singlerate = Rand(1, 100);
            if (singlerate == 1) inp << "B " << -1 << '\n';
            else inp << "B " << Rand(1, nodeNum) << '\n';
            nodeNum++;
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
        if (Curtest <= 10) Gen(inp, 2000);
        else if (Curtest <= 20) Gen(inp, 20000);
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