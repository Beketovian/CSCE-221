#include <iostream>
using namespace std;

struct Node 
{
    int data;
    Node* next;
};

//Q1
void printLots(Node* L, Node* P)
{
    Node* LCurr = L;
    int i = 0;
    while (LCurr != nullptr && P != nullptr)
    {
        if (P->data == i)
        {
            cout << LCurr->data << ", ";
            P = P->next;
        }
        LCurr = LCurr->next;
        i++;
    }
}

//Q2
void reverselist(Node* head)
{
    Node* prev = NULL;
    Node* nextNode = NULL;
    Node* curr = head;
    //reverse
    while(curr)
    {
        nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    head = prev;
    curr = head;
    //to print
    while(curr)
    {
        cout << curr->data << ", ";
        curr = curr->next;
    }
}

//Q3
Node* intersection(Node* L1, Node* L2)
{
    Node* curr1 = L1;
    Node* curr2 = L2;
    Node* ans = NULL;
    //use tail to keep track of last element to eliminate need to traverse until end every time
    Node* tail = NULL;

    while (curr1 != NULL && curr2 != NULL)
    {
        //if they intersect
        if (curr1->data == curr2->data)
        {
            //create new temporary node to store curr1 data
            Node* temp = new Node;
            temp->data = curr1->data;
            temp->next = NULL;
            //if ans empty
            if (ans == NULL)
            {
                ans = temp;
                tail = ans;
            }
            //add temp node to the end of ans
            else
            {
                tail->next = temp;
                tail = tail->next;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        //else advance curr1 or curr2 based on which is smaller (advance smaller one so that there is possibility of intersection)
        else if (curr1->data < curr2->data) {
            curr1 = curr1->next;
        }
        else {
            curr2 = curr2->next;
        }
    }
    return ans;
}


int main()
{    
    //Q1
    // //L is 1,2,3,4,5,6,7,8,9,10
    // Node* L = new Node {1, new Node {2, new Node {3, new Node {4, new Node {5,
    //           new Node {6, new Node {7, new Node {8, new Node {9, new Node {10, nullptr}}}}}}}}}};
    
    // // P is 1,3,4,6
    // Node* P = new Node {1, new Node {3, new Node {4, new Node {6, nullptr}}}};

    // cout << "Q1: ";
    // printLots(L, P); 
    // cout << endl;
    
    // //free memory
    // while (L != nullptr) {
    //     Node* temp = L;
    //     L = L->next;
    //     delete temp;
    // }
    // while (P != nullptr) {
    //     Node* temp = P;
    //     P = P->next;
    //     delete temp;
    // }
    
    //Q2
    // Node* head = new Node;
    // head->data = 1;
    // head->next = new Node;
    // head->next->data = 2;
    // head->next->next = new Node;
    // head->next->next->data = 3;
    // head->next->next->next = new Node;
    // head->next->next->next->data = 4;
    // head->next->next->next->next = NULL;

    // // Print the original linked list
    // cout << "Original linked list: ";
    // Node* current = head;
    // while (current != NULL) {
    //     cout << current->data << " ";
    //     current = current->next;
    // }
    // cout << endl;

    // // Print the reversed linked list
    // cout << "Reversed linked list: ";
    // reverselist(head);
    // cout << endl;

    //Q3
    Node* L1 = new Node;
    L1->data = 0;
    L1->next = new Node;
    L1->next->data = 2;
    L1->next->next = new Node;
    L1->next->next->data = 4;
    L1->next->next->next = new Node;
    L1->next->next->next->data = 6;
    L1->next->next->next->next = NULL;

    Node* L2 = new Node;
    L2->data = 1;
    L2->next = new Node;
    L2->next->data = 2;
    L2->next->next = new Node;
    L2->next->next->data = 3;
    L2->next->next->next = new Node;
    L2->next->next->next->data = 6;
    L2->next->next->next->next = new Node;
    L2->next->next->next->next->data = 7;
    L2->next->next->next->next->next = NULL;

    Node* result = intersection(L1, L2);
    Node* current = result;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;

    return 0;
}



//problem 2

