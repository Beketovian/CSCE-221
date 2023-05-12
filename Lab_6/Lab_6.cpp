#include <iostream>

// define the BinaryNode struct
struct BinaryNode {
    int value;
    BinaryNode* left;
    BinaryNode* right;
};


//Traverse down left side until we reach left leaf. Return left leaf if we reach, otherwise call function recursively
BinaryNode* BSTMinimum(BinaryNode* v)
{
    //if empty return null
    if(v == NULL)
    {
        return NULL;
    }
    //if we reach left leaf, return it
    if(v->left == NULL)
    {
        return v;
    }
    return BSTMinimum(v->left);
}

//If empty, set it to root. Find location for u with comparisons to v
void BSTInsert(BinaryNode* u, BinaryNode* v)
{
    //if v empty, set u as the root
    if(v == NULL)
    {
        v = u;
        return;
    }
//left
    //if u < v, insert u to left
    if(u->value < v->value)
    {
        //if v->left is null, set it to u
        if(v->left == NULL)
        {
            v->left = u;
        }
        //else, continue down left side
        else
        {
            BSTInsert(u, v->left);
        }
    }
//right
    //if u >= v, insert u to right
    if(u->value >= v->value)
    {
        //if v->right is null, set it to u
        if(v->right == NULL)
        {
            v->right = u;
        }
        //else, continue down right side
        else
        {
            BSTInsert(u, v->right);
        }
    }
}


// test the BSTMinimum() function
int main() {
    // create a sample binary search tree
    BinaryNode* root = new BinaryNode{4, 
                                new BinaryNode{2, 
                                    new BinaryNode{1, nullptr, nullptr},
                                    new BinaryNode{3, nullptr, nullptr}
                                }, 
                                new BinaryNode{6, 
                                    new BinaryNode{5, nullptr, nullptr},
                                    new BinaryNode{7, nullptr, nullptr}
                                }
                            };

    // get the minimum node
    BinaryNode* minNode = BSTMinimum(root);

    // print the value of the minimum node
    std::cout << "Minimum value: " << minNode->value << std::endl;

    return 0;
}

