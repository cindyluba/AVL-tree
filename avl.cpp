#include "avl.h"
#include <iostream>
#include <string>
#include <stddef.h>
#include <fstream>


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
    int wordCount;
};
 
int AVL::height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
int AVL::max(int a, int b)
{
    return (a > b)? a : b;
}
 
struct Node* AVL::newNode(string key)
{
    struct Node* node = new Node;

    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    node->wordCount = 1;
    return(node);
}
 
struct Node* AVL::rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
    x->right = y;
    y->left = T2;
 
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    return x;
}
 
struct Node* AVL::leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    return y;
}
 
int AVL::getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
struct Node* AVL::insert(struct Node* node, string key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else {
        node->wordCount = node->wordCount + 1;
        return node;
    }

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));
 
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
 
void AVL::inOrder(struct Node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        cout << root->key << "  " << root->wordCount << endl;
        inOrder(root->right);
    }
}

bool AVL::search(struct Node* node, string key) {
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

struct Node* AVL::minValueNode(struct Node* node)
{
    struct Node* current = node;
 
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
struct Node* AVL::deleteNode(struct Node* root, string key)
{
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;

    if ( key < root->key )
        root->left = deleteNode(root->left, key);
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
    else
    {
        if(root->wordCount > 1) {
            root->wordCount = root->wordCount - 1;
            return root;
        }
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
                *root = *temp; 
            free(temp);
        }
        else
        {
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)  return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left), height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
  
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

void AVL::sort(struct Node* root) {
    ofstream outFile;
    outFile.open("output.txt");
    sort(root, outFile);
    outFile << endl;
    outFile.close();
}

void AVL::sort(struct Node* root, ofstream& outFile) {
    if (root == NULL)
        return;
    sort(root->left, outFile);
    outFile << root->key << endl;
    sort(root->right, outFile);
}

void AVL::rangeSearch(struct Node* root, string startKey, string endKey) {
    if(root == NULL) return;
    if(startKey < root->key)
        rangeSearch(root->left, startKey, endKey);
    if(startKey <= root->key && endKey >= root->key)
        cout << root->key << endl;
    if(endKey > root->key)
        rangeSearch(root->right, startKey, endKey);
}


