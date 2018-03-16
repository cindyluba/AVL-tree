#ifndef tree25_h
#define tree25_h
#include <string>
#include "tree25node.h"

using namespace std;

class Tree25Node;

class Tree25
{
    Tree25Node *root; // Pointer to root node
    int t;  // Minimum degree
public:
    Tree25(int _t);
    void traverse();
    Tree25Node* search(string k);
    void insert(string k);

};

#endif
