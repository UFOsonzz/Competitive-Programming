#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int MAXN = 2e5;
const string ProbName = "P1";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

int n, bfs[MAXN + 5], dfs[MAXN + 5];

void Gen(ofstream& inp, int limN) {
    n = Rand(3, limN);

    inp << n << '\n';

    vector<int> shuffle(n - 2);
    iota(shuffle.begin(), shuffle.end(), 3);

    random_shuffle(shuffle.begin(), shuffle.end());

    for (int i = 1; i <= n; i++) 
        if (i <= 2) bfs[i] = i;
        else bfs[i] = shuffle[i - 3];

    random_shuffle(shuffle.begin(), shuffle.end());

    for (int i = 1; i <= n; i++) 
        if (i <= 2) dfs[i] = i;
        else dfs[i] = shuffle[i - 3];

    if (Rand(0, 10) == 0) swap(dfs[2], dfs[n]);

    for (int i = 1; i <= n; i++)
        inp << bfs[i] << " ";
    
    inp << '\n';
    for (int i = 1; i <= n; i++)
        inp << dfs[i] << " ";

    inp.close();
}

int main() {

    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        // system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 20);
        else if (Curtest <= 20) Gen(inp, 2000);
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