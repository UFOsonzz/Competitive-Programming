#include <bits/stdc++.h>

using namespace std;
#define int long long

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int tc; 
    cin >> tc; 
    while (tc--) { 
        int n; 
        cin >> n; 
        int a = -1, b = -1; 
        for (int i = 2; i <= 1e6; i++) {
            if (n % i == 0) { 
                if (n % (i * i) == 0) { 
                    a = i; 
                    b = n / i / i; 
                } else { 
                    a = sqrt(n / i); 
                    b = i; 
                }
                
                break; 
            }
        }

        cout << a  << " " << b << '\n'; 
    }
}
