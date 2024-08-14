#include <bits/stdc++.h>
using namespace std;

const int Testnum = 21;
const int MAXN = 1e5;
const int MAXM = 2e5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
    return l + rng() % (r - l + 1);
}


int main() {
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string Inpname = "test" + to_string(Curtest) + ".out";
        ifstream input_file(Inpname);

        if (!input_file) {
            cerr << "Khong tim thay file " << Inpname << '\n';
            continue;
        }

        stringstream Buffer;
        Buffer << input_file.rdbuf();

        string file_content = Buffer.str();

        replace(file_content.begin(), file_content.end(), 'B', 'L');
        replace(file_content.begin(), file_content.end(), 'H', 'N');

        input_file.close();

        ofstream output_file(Inpname);

        if (!output_file) {
            cerr << "Khong tim thay file " << Inpname << '\n';
            continue;
        }

        output_file << file_content;
        output_file.close();
    }


}