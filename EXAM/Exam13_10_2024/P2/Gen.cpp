#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const int MAXN = 5e5;
const string ProbName = "P2";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}

void Gen(ofstream& inp, int limN, int limK) {
    int n = Rand(1, limN); // Số lượng quân lính
    int k = Rand(1, limK); // Sức mạnh quái vật

    inp << n << " " << k << '\n';

    // Tạo ra sức mạnh quân lính
    vector<int> strengths(n);

    // Sinh sức mạnh quân lính sao cho có sự đa dạng
    for (int i = 0; i < n; ++i) {
        if (Rand(1, 10) == 1) 
            strengths[i] = 0;
        else strengths[i] = Rand(0, k / 5); 
    }

    // In ra sức mạnh của quân lính
    for (int i = 0; i < n; ++i) {
        inp << strengths[i] << " ";
    }
    inp << '\n'; // Thêm dòng mới sau khi in hết sức mạnh
    inp.close();
}

int main() {
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        // system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 10) Gen(inp, 20, 5000);
        else if (Curtest <= 20) Gen(inp, 400, 400);
        else Gen(inp, 5000, 5000);
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
