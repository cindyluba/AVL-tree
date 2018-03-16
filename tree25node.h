#ifndef tree25node_h
#define tree25node_h
#include <string>
#include <iostream>
#include "tree25.h"

using namespace std;
 
// A BTree node
class Tree25Node
{
    string *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    Tree25Node **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
public:
    Tree25Node(int _t, bool _leaf);
    void traverse(); 
    Tree25Node *search(string k);  
    void insertNonFull(string k);
    void splitChild(int i, Tree25Node *y);


friend class Tree25;
};

#endif

