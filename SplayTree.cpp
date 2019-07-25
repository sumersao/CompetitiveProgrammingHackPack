#include "SplayTree.h"
using namespace std;

SplayTree::SplayTree(size_t nElems) {
  root = treeFor(0, nElems);
  leftTree = nullptr;
  rightTree = nullptr;
  rightOfLeftTree = nullptr;
  leftOfRightTree = nullptr;
}

/**
 * Constructs a perfectly balanced tree for the values in the range
 * [low, high).
 */
SplayTree::Node*
SplayTree::treeFor(size_t low, size_t high) {
  /* Base Case: The empty range is represented by an empty tree. */
  if (low == high) return nullptr;
  
  /* Otherwise, pull out the middle, then recursively construct trees for the
   * left and right ranges.
   */
  size_t mid = low + (high - low) / 2;
  return new Node {
    mid,
    treeFor(low, mid),
    treeFor(mid + 1, high)
  };
}

/**
 * Frees all memory used by this tree.
 */
SplayTree::~SplayTree() {
  /* This is the same algorithm we used in PS3. It takes time O(n) and uses
   * only O(1) auxiliary memory.
   */
  while (root != nullptr) {
    /* If the root has no left subtree, just delete the root. */
    if (root->left == nullptr) {
      Node* next = root->right;
      delete root;
      root = next;
    }
    /* Otherwise, the root has a left subtree. Do a right rotation to move
     * that child to the left.
     */
    else {
      Node* child = root->left;
      root->left = child->right;
      child->right = root;
      root = child;
    }
  }
}

//Perform the assemble operation as detailed in the paper
void SplayTree::assemble() const {
  Node * A = root->left;
  Node * B = root->right;
  link_right(A);
  link_left(B);
  root->left = leftTree;
  root->right = rightTree;
  leftTree = nullptr;
  rightTree = nullptr;
  rightOfLeftTree = nullptr;
  leftOfRightTree = nullptr;
}

//This is the zig case for left
void SplayTree::case_one() const {
    Node * x = root;
    root = root->left;
    x->left = nullptr;
    link_left(x);
}

//This is the zig case for right
void SplayTree::case_one_opposite() const {
    Node * x = root;
    root = root->right;
    x->right = nullptr;
    link_right(x);
}

//Adds to leftmost node of right tree
void SplayTree::link_left(Node * n) const { 
    if(leftOfRightTree == nullptr) {
        rightTree = n;
        leftOfRightTree = n;
    }
    else {
        leftOfRightTree->left = n;
        leftOfRightTree = n;
    }
}

//Adds to rightmost node of left tree
void SplayTree::link_right(Node * n) const { 
    if(rightOfLeftTree == nullptr) {
        leftTree = n;
        rightOfLeftTree = n;
    }
    else {
        rightOfLeftTree->right = n;
        rightOfLeftTree = n;
    }
}

/**
 * Determines whether the specified key is present in the splay tree.
 */
bool SplayTree::contains(size_t key) const {
  //Base case, we found our element
  if(root->key == key)
  {
    assemble();
    return true;
  } else if(key < root->key)
  {
    //Element not in tree
    if(root->left == nullptr)
    {
      assemble();
      return false;
    } 
    size_t y_val = root->left->key;
    //zig case and found it
    if(key == y_val) //Case 1
    {
        case_one();
        assemble();
        return true;
    } 
    else if(key < y_val) //Case 2
    {
        //not in tree
        Node * z = root->left->left;
        if(z == nullptr) { //Case 2.1
            case_one();
            assemble();
            return false;
        }
        //zig-zig case
        else { //Case 2.2
            Node * x = root;
            Node * y = root->left;
            Node * B = y->right;
            x->left = B;
            y->left = nullptr;
            y->right = x;
            link_left(y);
            root = z;
            return contains(key);
        }
    }
    else //Case 3
    { // key > y_val, or case 3
        Node * z = root->left->right;
        //not in tree
        if(z == nullptr) {
            case_one();
            assemble();
            return false;
        } 
        //zig zag case
        else { //Case 3.2
            Node * x = root;
            Node * y = root->left;

            x->left = nullptr;
            y->right = nullptr;
            link_right(y);
            link_left(x);
            root = z;
            return contains(key);
        }
    }
  }
  else
  {
    //not in tree
    if(root->right == nullptr)
    {
      assemble();
      return false;
    } 
    size_t y_val = root->right->key;
    //zig case
    if(key == y_val) //Case 1
    {
        case_one_opposite();
        assemble();
        return true;
    } 
    else if(key > y_val) //Case 2
    {
        Node * z = root->right->right;
        //not in tree
        if(z == nullptr) { //Case 2.1
            case_one_opposite();
            assemble();
            return false;
        }
        //zig-zig case
        else { //Case 2.2
            Node * x = root;
            Node * y = root->right;
            Node * B = y->left;
            x->right = B;
            y->right = nullptr;
            y->left = x;
            link_right(y);
            root = z;
            return contains(key);
        }
    }
    else //Case 3
    { // key > y_val, or case 3
        Node * z = root->right->left;
        //not in tree
        if(z == nullptr) {
            case_one_opposite();
            assemble();
            return false;
        } 
        //zig-zag case
        else { //Case 3.2
            Node * x = root;
            Node * y = root->right;

            x->right = nullptr;
            y->left = nullptr;
            link_left(y);
            link_right(x);
            root = z;
            return contains(key);
        }
    }
  }
}
