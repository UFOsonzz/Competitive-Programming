#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const string ProbName = "P2";
const int MAXN = 1e6;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long Rand(long long l, long long r) {
    return l + rng() % (r - l + 1);
}

void Case(ofstream&inp, int n, int lim) {
    inp << n << '\n';
    vector<int> tmp_val;
    for (int i = 1; i <= n; i++) {
        int od = Rand(1, 3);
        int val;
        if (tmp_val.empty())
            od = 1;
        if (od == 3)
            od = 1;
        if (od == 1) {
            if (Rand(1, 10) == 1)
                val = 0;
            else val = Rand(1, lim), tmp_val.push_back(val);
        } else {
            int idx = Rand(0, (int)tmp_val.size() - 1);

            val = tmp_val[idx];
        }

        inp << od << " " << val << '\n';
    }
}

void Gen(ofstream& inp, int subtask) {
    
    int tot = 0;
    int t = Rand(1, 5);
    inp << t << '\n';
    for (int i = 1; i <= t; i++) {
        if (subtask == 1)
            Case(inp, Rand(1, 1e5), 10);
        else if (subtask == 2)
            Case(inp, Rand(1, 1000), 1e5);
        else Case(inp, Rand(1, 1e5), 1e5);
    }

    inp.close();
}


int main() {
    
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        //system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 1);
        else if (Curtest <= 20) Gen(inp, 2);
        else Gen(inp, 3);
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