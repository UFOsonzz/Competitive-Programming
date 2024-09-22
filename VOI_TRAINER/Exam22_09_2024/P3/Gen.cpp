#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int MAXN = 3e5;
const int MAXV = 1e9;
const string ProbName = "P3";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

int n, q;

void Gen(ofstream& inp, int limn, bool is2) {
    n = Rand(1, limn);
    q = Rand(1, (limn == 2000 ? 30 : n));
    
    set<pair<int, int>> edges;
    inp << n << " " << q << '\n';
    for (int i = 1; i <= n; i++) 
        inp << Rand(1, 1e9) << " ";
    inp << '\n';
    
    for (int i = 1; i <= q; i++) {
        int Case = Rand(0, 3);
        if (is2 && Case == 2) Case = 0;
        if (Case == 1 && edges.empty()) Case = 0;
        if (i == 1) Case = 0;
        if (Case == 0) {
            int u, v;
            do {
                u = Rand(1, n);
                v = Rand(1, n);
            } while (u == v || edges.count({u, v}) || edges.count({v, u}));
            inp << Case << " " << u << " " << v << '\n';
            edges.emplace(u, v);
        } else if (Case == 1) {
            int u = Rand(1, n);
            auto it = edges.lower_bound(make_pair(u, u));
            if (it == edges.end()) --it;
            inp << Case << " " << it->first << " " << it->second << '\n';
            edges.erase(it);
        } else if (Case == 2) {
            inp << Case << " " << Rand(1, n) << " " << Rand(1, MAXV) << '\n';
        } else {
            inp << Case << " " << Rand(1, n) << '\n';
        }

    }
}

int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        //system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 2000, 0);
        else if (Curtest <= 20) Gen(inp, MAXN, 1);
        else Gen(inp, MAXN, 0);

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