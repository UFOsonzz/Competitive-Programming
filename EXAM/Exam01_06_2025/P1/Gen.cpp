#include <bits/stdc++.h>
using namespace std;

const int Testnum = 50;
const string ProbName = "P1";
const int B = 1e5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long Rand(long long l, long long r) {
    return l + rng() % (r - l + 1);
}

const vector<long long> big_prime = {100000000003, 100000000019, 1000000007, 100000000057};
vector<long long> sieves;
bool is_prime[B + 5];
int small_lim;

void init_sieves() {
    memset(is_prime, true, sizeof(is_prime));
    for (long long i = 2; i <= B; i++) {
        if (is_prime[i]) {
            if (i <= 1000)
                small_lim = sieves.size();
            sieves.push_back(i);
            for (long long j = i * i; j <= B; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

void Gen(ofstream& inp, int subtask) {
    int tc = Rand(1, 20);
    inp << tc << '\n';
    while (tc--) {
        if (subtask == 1) {
            long long A = sieves[Rand(0, small_lim)];
            long long B = sieves[Rand(0, small_lim)];
            while (B == A) 
                B = sieves[Rand(0, small_lim)];
            
            inp << A * A * B << '\n';
        } else {
            if (Rand(0, 1)) {
                long long A = big_prime[Rand(0, 3)];
                long long B = sieves[Rand(0, small_lim)];
                inp << B * B * A << '\n';
            } else {
                long long A = sieves[Rand(0, (int)sieves.size() - 1)];
                long long B = sieves[Rand(0, (int)sieves.size() - 1)];
                while (B == A)
                    B = sieves[Rand(0, (int)sieves.size() - 1)];
                
                inp << A * A * B << '\n';
            }
        }
    }

    inp.close();
}


int main() {
    init_sieves();
    
    for (int Curtest = 1; Curtest <= Testnum; Curtest++) {
        string sub_folder = "test" + to_string(Curtest);
        // system(("mkdir " + sub_folder).c_str());
        string Inpname = sub_folder + "\\" + ProbName + ".inp";
        ofstream inp(Inpname);
        if (Curtest <= 15) Gen(inp, 1);
        else Gen(inp, 2);
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