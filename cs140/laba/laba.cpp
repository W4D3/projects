#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "laba.h"
using namespace std;

/*
   Mitchell Wade
   April 28, 2014
   LabA

   This program runs a simulation of an AVL tree that
   displays it in a vertical fashion of text lines. A
   user can insert some text into the tree, order the
   tree in post or prefixed notation, and also print 
   out different specifications of the tree or the 
   entire tree itself.

*/

BSTree::BSTree()
{
  sentinel = new BSTNode;
  sentinel->parent = NULL;
  sentinel->left = NULL;
  sentinel->right = sentinel;
  size = 0;
}

BSTree::~BSTree()
{
  recursive_destroy(sentinel->right);
  delete sentinel;
}

int BSTree::Insert(string s, void *val)
{
  BSTNode *parent;
  BSTNode *n;

  parent = sentinel;
  n = sentinel->right;

  while (n != sentinel) {
    if (n->key == s) return 0;
    parent = n;
    if (s < n->key) {
      n = n->left;
    } else {
      n = n->right;
    }
  }

  n = new BSTNode;
  n->key = s;
  n->val = val;
  n->parent = parent;
  n->left = sentinel;
  n->right = sentinel;
  if (parent == sentinel) {
    sentinel->right = n;
  } else if (s < parent->key) {
    parent->left = n;
  } else {
    parent->right = n;
  }
  size++;
  return 1;
}

void *BSTree::Find(string s)
{
  BSTNode *n;

  n = sentinel->right;
  while (1) {
    if (n == sentinel) return NULL;
    if (s == n->key) return n->val;
    if (s < n->key) {
      n = n->left;
    } else {
      n = n->right;
    }
  }
}

int BSTree::Delete(string s)
{
  BSTNode *n, *parent, *mlc;
  string tmpkey;
  void *tmpval;

  n = sentinel->right;
  while (n != sentinel && s != n->key) {
    if (s < n->key) {
      n = n->left;
    } else {
      n = n->right;
    }
  }
  if (n == sentinel) return 0;

  parent = n->parent;
  if (n->left == sentinel) {
    if (n == parent->left) {
      parent->left = n->right;
    } else {
      parent->right = n->right;
    }
    if (n->right != sentinel) n->right->parent = parent;
    delete n;
    size--;
  } else if (n->right == sentinel) {
    if (n == parent->left) {
      parent->left = n->left;
    } else {
      parent->right = n->left;
    }
    n->left->parent = parent;
    delete n;
    size--;
  } else {
    for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
    tmpkey = mlc->key;
    tmpval = mlc->val;
    Delete(tmpkey);
    n->key = tmpkey;
    n->val = tmpval;
  }
  return 1;
}

vector <void *>BSTree::Sorted_Vector()
{
  array.clear();
  recursive_make_vector(sentinel->right);
  return array;
}

void BSTree::Print()
{
  recursive_inorder_print(0, sentinel->right);
}

int BSTree::Size()
{
  return size;
}

int BSTree::Empty()
{
  return (size == 0);
}

void BSTree::recursive_inorder_print(int level, BSTNode *n)
{
  if (n == sentinel) return;
  recursive_inorder_print(level+2, n->right);
  printf("%*s%s\n", level, "", n->key.c_str());
  recursive_inorder_print(level+2, n->left);
}

void BSTree::recursive_make_vector(BSTNode *n)
{
  if (n == sentinel) return;
  recursive_make_vector(n->left);
  array.push_back(n->val);
  recursive_make_vector(n->right);
}

void BSTree::recursive_destroy(BSTNode *n)
{
  if (n == sentinel) return;
  recursive_destroy(n->left);
  recursive_destroy(n->right);
  delete n;
}

// METHODS //

/* Recursively find the height of the tree */
int BSTree::recursive_height(BSTNode *n) { 

    int left = 0, right = 0;

    /* Node not found */
    if (n == NULL) return -1;

    /* Node is sentinel */
    if (n->left == sentinel && n->right == sentinel)
        return 0; 
    
    /* Look for next node */
    if (n->left != sentinel) 
        left = recursive_height(n->left); 
    
    /* Look for next node */
    if(n->right != sentinel) 
        right = recursive_height(n->right); 
    
    /* Add one to left or right if found */
    if(left > right) return left + 1; 
    else return right + 1;
}

/* Recursively get height and check if AVL */
int BSTree::recursive_height_and_avl_check(BSTNode *n)  {
    
    int height = 0; 
    int height1 = 0; 
    
    /* If it is the sentinel return -1 */
    if (n == sentinel) return -1; 
    
    /* Recursively check the tree */
    height = 1+recursive_height_and_avl_check(n->left); 
    height1 = 1+recursive_height_and_avl_check(n->right); 
    
    /* Return -2 if it is not an AVL tree */
    if (abs(height-height1) > 1 || height == -1 || height1 == -1) return -2; 
    
    /* Return the height of the node if it's a legal AVL tree */
    if (height > height1) return height; 
    
    return height1; 
}

/* How the tree is traversed */
void BSTree::recursive_preorder(int level, BSTNode *n) { 

    if (n == sentinel) return; 
    
    /* Print out the nodes */
    printf("%*s%s\n", level, "", n->key.c_str()); 
    recursive_preorder(level+2, n->left); 
    recursive_preorder(level+2, n->right); 
}

/* How the tree is traversed */
void BSTree::recursive_postorder(int level, BSTNode *n) { 
    
    if (n == sentinel) return; 
    
    /* Print out the nodes */
    recursive_postorder(level+2, n->left); 
    recursive_postorder(level+2, n->right); 
    printf("%*s%s\n", level, "", n->key.c_str()); 
}

/* Recursively prints the tree in postorder notation */
void BSTree::Postorder() {
    
    recursive_postorder(0, sentinel->right);
}

/* Recursively prints the tree in preorder notation */
void BSTree::Preorder() {

    recursive_preorder(0, sentinel->right);
}

/* Return the depth of the tree */
int BSTree::Depth(string key) {
     
    int depth = 0; 
    BSTNode *parent;
    BSTNode *n;
    
    
    /* Set nodes */
    parent = sentinel;
    n = sentinel->right;
    
    while (n != sentinel) {

        if (n->key == key) return depth;
        
        /* Set next node and increment depth */
        parent = n; 
        depth++;
        
        /* Go to next node */
        if (key < n->key) {
            n = n->left; 
        } else {
            n = n->right; 
        }
    }

     return -1;
}

/* Return the height of the tree */
int BSTree::Height() {
    
    /* If tree is empty  */
    if (Size() == 0) {
        return -1;
    }
    
    return recursive_height(sentinel)-1;
}

/* Check if AVL or not */
int BSTree::IsAVL() {
    
    /* If it is the sentinel return 1 */
    if (sentinel->right == sentinel) return 1; 
    
    /* Get the node, avl or not */
    int test = recursive_height_and_avl_check(sentinel->right); 
    
    /* Return 0 if not a legal AVL tree */
    if (test == -2) return 0; 
    
    /* Return 1 if it is a legal AVL tree */
    return 1; 
}

/* Second find function with BSTNode variable given */
BSTNode *Find2(string key, BSTNode *sentinel) {
    
    BSTNode *n; 
    
    /* Set initial node */
    n = sentinel->right; 
    
    while (n != sentinel) { 
        
        /* Return node if found */
        if (key == n->key) 
            return n;
    
        /* Check left */
        if (key < n->key) { 
            n = n->left; 
        } else { 

            /* Check right */
            n = n->right; 
        } 
    } 
    
    /* If not found */
    return NULL;
}

/* Rotate the nodes */
int BSTree::Rotate(string key) {
    
    BSTNode *n = Find2(key, sentinel); 
    BSTNode *child;
    BSTNode *parent;
    BSTNode *grandparent;
    
    /* Didn't find the node */
    if(n == NULL) return 0;
    
    /* If the node is the sentinel */
    if(n == sentinel) return 0;

    /* Set the nodes */
    parent = n-> parent;
    grandparent = n->parent->parent;
    
    /* Can't rotate at root */
    if(n->parent == sentinel) return 0;

    /* If it's the left child */
    if(n->key > n->parent->key) {
        child = n->left;
        child->parent = parent;
        parent->right = child;
        parent->parent = n;
        n->left = parent;
        
        if(grandparent->key > n->key)
            grandparent->left = n;
        else 
            grandparent->right = n;
        n->parent = grandparent;
        return 1;
    }
    
    /* If it's the right child */
    else{
        child = n->right;
        child -> parent = parent;
        parent->left = child;
        parent->parent = n;
        n->right = parent;
        
        if(grandparent -> key > n-> key)
            grandparent->left = n;
        else
            grandparent->right = n;
        n->parent = grandparent;
        return 1;
    }
}
