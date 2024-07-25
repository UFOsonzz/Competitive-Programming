import math 
Limit = int(2e5 + 5)
def CompValue_Convert(x, aojNumber) :
    return 0 if x == 1 else math.log2(math.log2(x)) + aojNumber
def solve() :
    n = int(input())
    Array_InputString = input()
    a = []
    a[0 : n] = map(int, Array_InputString.split())
    CompValue = []
    CompValue.append(CompValue_Convert(a[0], 0))
    ans = 0
    for i in range(1, n) :
        Bsle = 0
        Bsri = Limit
        aojNumber = -1
        if (a[i] == 1 and a[i] < a[i - 1]) :
            print(-1)
            return
        while (Bsle <= Bsri) :
            Bsmi = (Bsle + Bsri) // 2
            if (CompValue_Convert(a[i], Bsmi) >= CompValue[i - 1]) :
                aojNumber = Bsmi
                Bsri = Bsmi - 1
            else :
                Bsle = Bsmi + 1
        CompValue.append(CompValue_Convert(a[i], aojNumber))
        ans += aojNumber
    print(ans)
            
Test_num = int(input())
while (Test_num > 0) :
    Test_num -= 1
    solve() 