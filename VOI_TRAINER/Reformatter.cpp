#include <bits/stdc++.h>
using namespace std;

const int ProbNum = 3; // ProbNum
const int TestNum = 50; // TestNum

int main() {
    
    for (int i = 1; i <= TestNum; i++) {
        string folder_name = "test" + to_string(i);

        string inp_name = "test" + to_string(i) + ".inp";
        string newinp_name = "P" + to_string(ProbNum) + ".inp";

        string out_name = "test" + to_string(i) + ".out";
        string newout_name = "P" + to_string(ProbNum) + ".out";

        if ((system(("rename " + inp_name + " " + newinp_name).c_str()) == 0) &&
            (system(("rename " + out_name + " " + newout_name).c_str()) == 0) &&
            (system(("mkdir " + folder_name).c_str()) == 0) &&
            (system(("move " + newinp_name + " " + folder_name).c_str()) == 0) &&
            (system(("move " + newout_name + " " + folder_name).c_str()) == 0)) {
            cerr << "Created folder " << folder_name << "!\n"; 
        } else {
            cerr << "Error when creating folder " << folder_name << "!!!\n";
        }
    }
}