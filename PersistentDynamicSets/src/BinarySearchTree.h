#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <iostream>    
#include <vector>
#include <stack>
using namespace std;


template <typename Comparable>
class BinarySearchTree
{
private:  // this private BinaryNode is within BST
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        bool status;     // status = 0 if the node belongs to the tree with root r1 (it can also be in the tree with root r2); 
        //status = 1 means that the node only belongs to the tree with root r2

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt , bool st)
            : element( theElement ), left( lt ), right( rt ), status( st ) 
        { 
        }
    };

    BinaryNode *r1;    //r1 is the root of the BST for the persistent dynamic set
    BinaryNode *r2;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * if st=0, insert an element from the persistent dynamic set; st=1,otherwise
     */

    void insert(const Comparable & x, BinaryNode * & t, bool st)
    {
        //check if x is already present. If it is, do nothing as we don't want to repeat elements
        if(contains(x,r1) || contains(x,r2))
        {
            return;
        }
        //if node belongs to r1 root
        if(st == 0)
        {
            //if tree is empty, create new node
            if(t == nullptr)
            {
                t = new BinaryNode(x,nullptr,nullptr,st);
            }
            else
            {
                //determing if it left or right child and insert accordingly
                BinaryNode** child;
                if(x < t->element)
                {
                    child = &t->left;
                }
                else
                {
                    child = &t->right;
                }
                insert(x, *child, st);
                BinaryNode* temp = t;
                t = new BinaryNode(t->element, t->left, t->right, t->status);
                delete temp;
                temp = nullptr;
            }
        }
        //else if it's in tree with root r2
        else
        {
            //if cloned tree is empty, call helper and recursively call insert to follow persistent dynamic set structure
            if(r2 == nullptr)
            {
                r2 = getbranch(x, r1, st);
                insert(x, r2, st);
            }
            //if cloned tree is not empty, iterate until curr is nullptr
            else
            {
                BinaryNode* curr = r2;
                BinaryNode* prev = nullptr;

                while(curr != nullptr)
                {
                    //if curr is part of cloned subtree node, then clone the subtree
                    if(curr->status == 0)
                    {
                        BinaryNode** prev_child;
                        if(prev->right == curr)
                        {
                            prev_child = &prev->right;
                        }
                        else
                        {
                            prev_child = &prev->left;
                        }
                        *prev_child = getbranch(x, *prev_child, st);
                        curr = *prev_child;
                    }
                    //if curr is not a cloned node, update previous and curr to point to left or right subtree based on x's value
                    else
                    {
                        if(x < curr->element)
                        {
                            prev = curr;
                            curr = curr->left;
                        }
                        else
                        {
                            prev = curr;
                            curr = curr->right;
                        }
                    }
                }
                //create new node with the given status as a child of the previous node
                BinaryNode** new_child;
                if(x < prev->element)
                {
                    new_child = &prev->left;
                }
                else
                {
                    new_child = &prev->right;
                }
                *new_child = new BinaryNode(x, nullptr, nullptr, st);
            }
        }
    }

    BinaryNode* getbranch(const Comparable & x, BinaryNode *t, bool st)
    {
        //check for nullptr
        if(t == nullptr)
        {
            return nullptr;
        }
        //make new node with t->element and status
        BinaryNode* nn = new BinaryNode(t->element, nullptr, nullptr, st);
        //set right or left child with recursive getbranch calls, depending on x's value
        if(x < t->element)
        {
            nn->left = getbranch(x, t->left, st);
            nn->right = t->right;
        }
        else
        {
            nn->right = getbranch(x, t->right, st);
            nn->left = t->left;
        }
        return nn;
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * this function is only for the elements not in the persistent dynamic set
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if(t == nullptr || t->status == 0) //we cannot remove if it is part of r1
        {
            return;
        }
        if(x < t->element)
        {
            remove(x, t->left);
        }
        else if(x > t->element)
        {
            remove(x, t->right);
        }
        else if(t->left != nullptr && t->right != nullptr)
        {
            t->element = findMin(t->right);
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode *temp = t;
            if(t->left != nullptr)
            {
                t = t->left;
            }
            else
            {
                t = t->right;
            }
            delete temp;
            temp = nullptr;
        }
    }

    /**
     * Internal method to make subtree empty.
     * if st = 1, 't' is a node in the tree with root r2; otherwise, 
     * 't' is a node in the tree with root r1 
     * think about how to deal with 't' if 't' is a common node of the two
     * trees
     */
    void makeEmpty( BinaryNode * & t, bool st )
    {
        if(t != nullptr)
        {
            makeEmpty(t->left, st);
            makeEmpty(t->right, st);

            if(st == 1 && t->status == 1)
            {
                delete t;
                t = nullptr;
            }
            else if(st == 0 && t->status == 0)
            {
                delete t;
                t = nullptr;
            }
        }
    }

    /**
     * Internal method to clone subtree.
     * if st = 1, t is a node in the BST with root r1;
     * if st = 0, otherwise
     */
    BinaryNode * clone( BinaryNode *t, bool st ) const
    {
        if(t == nullptr)
        {
        return nullptr;
        }
        else
        {
            if(st)
            {
                if(t->status == 0)
                {
                    //find node with the same r1->element
                    BinaryNode *traverse = r1;
                    while(traverse->element != t->element)
                    {
                        if(t->element > traverse->element)
                        {
                            traverse = traverse->right;
                        }
                        else
                        {
                            traverse = traverse->left;
                        }
                    }
                    return traverse;
                }
                else
                {
                    // Create a new node and copy its properties recursively
                    BinaryNode *nNode = new BinaryNode(t->element, clone(t->left, st), clone(t->right, st), st);
                    return nNode;
                }
            }
            else
            {
                if(t != nullptr)
                {
                    // Create a new node and copy its properties recursively
                    BinaryNode *nNode = new BinaryNode(t->element, clone(t->left, st), clone(t->right, st), st);
                    return nNode;
                }
                else
                {
                    return nullptr;
                }
            }
        }
    // In case none of the above conditions are met, return null
    return nullptr;
    }

public:
    BinarySearchTree( ) :r1( NULL ), r2( NULL )
    {
    }

    BinarySearchTree( const BinarySearchTree & rhs ) 
    {
        *this = rhs;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( BinaryNode * t ) const
    {
        if(t == nullptr)
        {
            throw UnderflowException();
        }
        if(t->left == nullptr)
        {
            return t->element;
        }
        return findMin(t->left);
    }
    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( BinaryNode *t ) const
    {
        if(t == nullptr)
        {
            throw UnderflowException();
        }
        if(t->right == nullptr)
        {
            return t->element;
        }
        return findMax(t->right);
    }

    /**
    * Returns true if x is found in the subtree with root t.
    */
	bool contains( const Comparable & x, BinaryNode *t ) const 
    { 
        if(t == nullptr)
        {
            return false;
        }
        if(x < t->element)
        {
            return contains(x, t->left);
        }
        if(t->element < x)
        {
            return contains(x, t->right);
        }
        return true;
    }

    /**
     * returns the node with element = x in the subtree with root t
     * to make sure that x is always here, call contains(x, t) first
     */

    BinaryNode * search( const Comparable & x, BinaryNode *t ) const
    {
        if(t == nullptr)
        {
            return nullptr;
        }
        if(x < t->element)
        {
            return search(x, t->left);
        }
        if(t->element < x)
        {
            return search(x, t->right);
        }
        return t;
    } 


    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return r1 == NULL;
    }

    /**
     * Make the tree logically empty.
     * remove all items
     * pay attention to the common nodes in r1 and r2
     */
    void makeEmpty( )
    {
        makeEmpty(r2, 1);
        makeEmpty(r1, 0);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     * if st =0, insert into the tree with root r1; if st=1, insert into the
     * tree with root r2
     */
    void insert ( const Comparable & x, bool st)
    {
        if(st)
        {
            insert(x, r2, 1);
        }
        else
        {
            insert(x, r1, 0);
        }
    } 

    /**
     * Remove x from the tree with root r2. Nothing is done if x is not found
     * or if x is from the persistent dynamic set.
     */
    void remove( const Comparable & x )
    {
      remove(x, r2);
    }

    /**
     * Deep copy.
     * notice the common nodes in both trees
     */

    const BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            r1 = clone( rhs.r1, 0 );
            r2 = clone( rhs.r2, 1);
        }
        return *this;
    }

    /* in-order tree walk and the result is stored in v
     * the root is r
     */

    void inOrder ( vector <BinaryNode*> &v , BinaryNode * r)
    {
    stack<BinaryNode *> s;
    BinaryNode *curr = r;

    while(curr != nullptr || !s.empty())
    {
        while(curr != nullptr)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        v.push_back(curr);
        curr = curr->right;
    }
    }


  /* this function is to test
   * please do not change
   */
  void printTree( )     // Print tree in sorted order
  {
    vector <BinaryNode*> v1, v2;

    inOrder (v1, r1);   //inorder traverse
    inOrder (v2, r2);  //inorder traverse

   cout << "print BST for persistent dynamic set   " << endl;

   int i, j;
   for ( i = 0; i < v1.size(); i++)
   {
     cout <<  v1.at (i) -> element << "  ";
   }
   cout << endl;


  cout << "print BST for the whole input set   " << endl;

  for ( i = 0; i < v2.size(); i++)
  {
      cout << v2.at (i) -> element << "  ";
  }
  cout << endl;
 
  i=0; j=0;

  // output the common nodes with the same address in both trees
  // a common node in both trees must have the same address 
  cout << "Common nodes: ";
  while ( i < v1.size() )
  {
    if ( v1.at(i) -> element == v2.at(j) -> element )
    {
      if ( v1.at(i) == v2.at(j) )   // if the address are equal
      {
       cout << v1.at(i) -> element << "  "; 
      }

       i++; j++;
    }
    else if ( v2.at(j) -> element < v1.at(i) -> element )
      j++;
  }
  cout << endl;
  
 }

};


#endif