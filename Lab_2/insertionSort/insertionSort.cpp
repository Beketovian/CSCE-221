#include <iostream>
#include <assert.h>
using namespace std;

// TODO (student): sort the numbers into nonincreasing order using an insertion
// sort (5 points)
void insertionSort(int* arr, int size) 
{
    for(int j = 1; j < size; j++)
    {
        int temp = arr[j];
        int i = j-1;
        while(i >= 0 && arr[i] < temp)
        {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i+1] = temp;
    }
}

int main() {
    // Don't modify the main function
    int test1[] = {1, 3, 5, 7};
    int test2[] = {7, 5, 3, 1};
    int test3[] = {1, 7, 3, 7};

    insertionSort(test1, 4);
    assert(test1[0]==7);
    assert(test1[1]==5);
    assert(test1[2]==3);
    assert(test1[3]==1);
    cout << "Test 1 passed. " << endl;

    insertionSort(test2, 4);
    assert(test2[0]==7);
    assert(test2[1]==5);
    assert(test2[2]==3);
    assert(test2[3]==1);
    cout << "Test 2 passed. " << endl;

    insertionSort(test3, 4);
    assert(test3[0]==7);
    assert(test3[1]==7);
    assert(test3[2]==3);
    assert(test3[3]==1);
    cout << "Test 3 passed. " << endl;

    return 0;
}
