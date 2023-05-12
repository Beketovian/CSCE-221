// A C++ program to demonstrate common Binary Max-Heap Operations

#include<iostream>
#include <assert.h>
using namespace std;

//swap
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// implement this function to insert the element x into the heap
void insert(int heap[], int& n, int x)
{
    heap[n] = x; 
    int i = n; //keep track of the number of elements
    while(i > 0 && heap[(i-1)/2] < heap[i]) //swap node with its parent (at (i-1)/2) until max-heap property
    {
        swap(heap[i], heap[(i-1)/2]);
        i = (i-1)/2;
    }
    n++; //increment number of elements
}

// implement this function to remove the root
void remove(int heap[], int& n)
{
    heap[0] = heap[n-1]; //replace root with value of last node
    n--; //remove last node
    int i = 0;
    while(i < n) //swap root w/ greater child until max-heap property
    {
        if(2 * i + 2 < n) //if node has 2 children
        {
            if(heap[i] > heap[2 * i + 1] && heap[i] > heap[2 * i + 2]) //check for max-heap order
            {
                break;
            }
            else //else, swap node w/ greater child
            {
                int j;
                if(heap[2 * i + 1] > heap[2 * i + 2])
                {
                    j = 2 * i + 1;
                }
                else
                {
                    j = 2 * i + 2;
                }
                swap(heap[i], heap[j]);
                i = j;
            }
        }
        else //if node has 0 or 1 child
        {
            if(2 * i + 1 < n)
            {
                if(heap[i] < heap[2 * i + 1]) //swap node with child
                {
                    swap(heap[i], heap[2 * i + 1]);
                }
            }
            break;
        }
    }
}

int main() 
{
    int heap[100]; // The array to store the max-heap
    int n = 0;  // keep track the number of elements in the heap

    insert(heap, n, 1);
    insert(heap, n, 2);
    insert(heap, n, 4);
    insert(heap, n, 6); 
    insert(heap, n, 10);
    insert(heap, n, 11);
    insert(heap, n, 13);
    insert(heap, n, 15);

    assert(n==8);
    int sol1[] = {15, 13, 11, 6, 4, 2, 10, 1};
    int i = 0;

    for (i = 0; i < 8; i++)
        assert(heap[i]==sol1[i]);

    cout << "Test case 1 passed. " << endl;

    remove(heap, n);
    remove(heap, n);

    int sol2[] = {11, 6, 10, 1, 4, 2};
    for (i = 0; i < 6; i++)
        assert(heap[i]==sol2[i]);

    cout << "Test case 2 passed. " << endl;
    return 0;
}
