#include <cmath>
int main()
{
    //code for problem 2:
    // int sum = 0;
    // int n = 1000;
    // for(int i = 0; i < n;i++)
    //     {
    //     for(int j = 0; j < n-i; j++)
    //     {
    //         sum=sum+i+j;
    //     }
    // }
    // return 0;
    
    //code for problem 3:
    int tot = 0;
    int n = 5;
    int x = 3;
    int a[5] = {1,2,3,4,5};
    for(int i = 0; i < n; i++)
    {
        tot += a[i]*pow(x,i);
    }

}


