#include "avl.h"
#include <iostream>
#include <string>
#include <stddef.h>

using namespace std;

AVL::AVL() {
}

AVL::~AVL() {
}

// An AVL tree node
struct Node
{
    string key;
    struct Node *left;
    struct Node *right;
    int height;
};
 
// A utility function to get height of the tree
int AVL::height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int AVL::max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* AVL::newNode(string key)
{
    struct Node* node = new Node;
                        //malloc(sizeof(struct Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node* AVL::rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node* AVL::leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int AVL::getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert key in subtree rooted
// with node and returns new root of subtree.
struct Node* AVL::insert(struct Node* node, string key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void AVL::inOrder(struct Node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        cout << root->key << endl;
        inOrder(root->right);
    }
}

bool AVL::seasrch(struct Node* node, string key) {
    if(node == NULL) {
        return false;
    } 
    if(key.compare(node->key) > 0) {
        return search(node->right, key);
    } else if(key.compare(node->key) < 0) {
        return search(node->left, key);
    } else {
        return true;
    }
}
 
/* Drier program to test above function*/
// int main()
// {
//   struct Node *root = NULL;
 
//   /* Constructing tree given in the above figure */
//   root = insert(root, 10);
//   root = insert(root, 20);
//   root = insert(root, 30);
//   root = insert(root, 40);
//   root = insert(root, 50);
//   root = insert(root, 25);
 
//   /* The constructed AVL Tree would be
//             30
//            /  \
//          20   40
//         /  \     \
//        10  25    50
//   */
 
//   cout << "Preorder traversal of the constructed AVL tree is" << endl;;
//   preOrder(root);
 
//   return 0;
// }
