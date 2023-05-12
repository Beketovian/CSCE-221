#include <iostream>
#include <assert.h>
using namespace std;


// TODO (student): sort the numbers into nonincreasing order using a merge sort
// TODO (student): implement the following two functions
void merge(int* A, int p, int q, int r) {
    //find left and right side size
    const int left = q-p+1;
    const int right = r-q;
    //make left and right arrays
    int *leftarr = new int[left];
    int *rightarr = new int[right];
    //copy values to left and right arrays
    for(int i = 0; i < left; i++)
    {
        leftarr[i] = A[i+p];
    }
    for(int i = 0; i < right; i++)
    {
        rightarr[i] = A[i+q+1];
    }
    //merge left and right arrays
    int i = 0; //left array index
    int j = 0; //right array index
    int k = p; //k will be incremented
    while(i < left && j < right)
    {
        if(leftarr[i] >= rightarr[j])
        {
            A[k++] = leftarr[i++];
        }
        else
        {
            A[k++] = rightarr[j++];
        }
    }
    while (i < left)
    {
        A[k++] = leftarr[i++];
    }
    while (j < right)
    {
        A[k++] = rightarr[j++];
    }
    delete[] leftarr;
    delete[] rightarr;
}

void mergeSort(int* A, int p, int r) {
    if(p<r)
    {
    int mid = (r-p)/2 + p;
    mergeSort(A, p, mid);
    mergeSort(A, mid + 1, r);
    merge(A, p, mid, r);
    }
}

int main() {
    // Don't modify the main function
    int test[] = {100, 3, 45, 7, 45, 57, 34, 12, 10};
    int sol[] = {100, 57, 45, 45, 34, 12, 10, 7, 3};
    mergeSort(test, 0, 8);

    for (int i = 0; i < 9; i++)
        assert(test[i]==sol[i]);

    cout << "Test passed." << endl;

    return 0;
}
