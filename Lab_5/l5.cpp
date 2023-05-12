#include <iostream>
#include <math.h>
using namespace std;

int alg(int a, int n)
{
    if(n == 1)
    {
        return a;
    }
    if(n % 2 == 0)
    {
        int R = pow(a,n/2);
        return R*R;
    }
    else
    {
        int R = pow(a,(n-1)/2);
        return R*R*a;
    }
}
int main()
{
    int a = 2;
    int n = 5;
    int res = alg(a,n);
    cout << res;
}