#include <iostream>
#include "Leaf.h"
#include "Stem.h"

Stem::Stem() {
    //initialize
    front = nullptr;
    back = nullptr;
    next = nullptr;
    value = 0;
    frequency = 0;
}

Stem::~Stem() {
    //free allocated memory
    Leaf* curr = front;
    while(curr != nullptr)
    {
    front = front->next;
    delete curr;
    curr = front;
    }
}

//make function for if equal, as we will need to call this more than once.
//Because we don't need to made a new node, we just need to increase front count, increase frequency, and return FALSE
/*
bool Stem::eq()
{
    (front->count)++;
    frequency++;
    return false;
}
*/

//return true at end if successfully inserted
bool Stem::insert(int value) {
    //if empty then create new node w/ value, freq will be 1
    if(front == nullptr)
    {
        front = new Leaf{value, 1, nullptr};
        back = front;
        frequency = 1;
        return true;
    }
    //if value is less than front val, create new node and set it to front
    if(value < front->value)
    {
        front = new Leaf{value, 1, front};
        frequency++;
        return true;
    }
    
    //if equal, increment count of front node and frequency++. return false as we did not insert
    if(value == front->value)
    {
        (front->count)++;
        frequency++;
        return false;
        //eq();
    }

    //if greater, traverse all nodes until spot is found for it
    //curr and prev for traversal
    Leaf* prev = front;
    Leaf* curr = front->next;
    
    while(curr != nullptr && value >= curr->value)
    {
        //if we see duplicate value, increment ct and freq
        if(value == curr->value)
        {
            (curr->count)++;
            frequency++;
            return false;
            //eq();
        }
        prev = curr;
        curr = curr->next;
    }
    //duplicate not found, create new node. freq will be 1 as this is a new node
    prev->next = new Leaf{value, 1, curr};
    if(curr == nullptr)
    {
        back = prev->next;
    }
    frequency++;
    return true;    
}

//return true is a leaf is deleted 
bool Stem::remove(int target) {
    /*Check for if list is empty. If it is then return false as there is nothing to delete. Also,
    if value we want to delete is less than front (smallest value), then it is not present in the list*/
    if(front == nullptr || target < front->value)
    {
        return false;
    }
    /*Check for if target is equal to front value. If it is then decrement front count and freq.
    If the front count > 1, we aren't deleting a leaf, only lowering the freq and count, so return false*/
    if(target == front->value)
    {
        if(front->count > 1)
        {
            (front->count)--;
            frequency--;
            return false;
        }
        //otherwise, we are deleting a leaf so create temp, do deletion, and return true
        Leaf* temp = front;
        front = front->next;
        //if empty, set back to nullptr as well
        if(front == nullptr)
        {
            back = nullptr;
        }
        delete temp;
        frequency--;
        return true;
    }
    //if deleted value not front of list, go through list until target is found and do a deletion
    Leaf* prev = front;
    Leaf* curr = front->next;
    while(curr != nullptr && target >= curr->value)
    {
        if(target == curr->value)
        {
            if(curr->count > 1)
            {
                (curr->count)--;
                frequency--;
                return false;
            }
            prev->next = curr->next;
            if(curr == back)
            {
                back = prev;
            }
            delete curr;
            frequency--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

// Don't modify
std::ostream &operator << (std::ostream &out, const Stem &x) {
  out << x.value <<" | ";
  Leaf *CURLEAF_ptr = x.front;  

  while ( CURLEAF_ptr != nullptr )
  {
    out << *CURLEAF_ptr <<" ";
    CURLEAF_ptr = CURLEAF_ptr -> next;
  }
  out << std::endl;

  return out;
}

