#include <iostream>
#include <assert.h>
using namespace std;


// TODO (student): implement binary search
// return -1 is key is not present in the subarray A[p...r]
// return the index if key is present in the subarray A[p...r]

int binarySearch(int* A, int p, int r, int key) {
    int middle;
    while(p<=r)
    {
        middle = (r-p)/2 + p;
        //find if key in array, return the index of where it is
        if(A[middle] == key)
        {
            return middle;
        }
        //if key less than middle, look through left half of array
        else if(A[middle] > key)
        {
            r = middle-1;
        }
        //else search right side of array
        else
        {
            p = middle+1;
        }
    }
    return -1;

}

int main() {
    // Don't modify the main function
    int test[] = {3, 7, 10, 12, 34, 45, 45, 57, 100};
    int index = 0;
    for(int i = 0; i < 9; i++)
    {
        index = binarySearch(test, 0, 8, test[i]);
        assert(test[index] == test[i]);
    }
    index = binarySearch(test, 0, 8, -10);
    assert(index == -1);
    
    cout << "Tests passed." << endl;

    return 0;
}
