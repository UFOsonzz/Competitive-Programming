#include <bits/stdc++.h>
using namespace std;

int main() {
    /*
        Pseudo :
        voi moi family thi ta giai quyet bai toan tim doan con co tong lon nhat do dai k voi k = [1...n]
            tong cua mot doan do dai k = pre[i] - pre[i - k], neu coi day A la pre[] 
            coi day B la -pre[]
            thi bai toan tro ve tim day C[] co C[k] = max(A[i] + B[j]) voi i + j = k
            --> giai quyet bang viec xet dan cac convex hull
    */

}