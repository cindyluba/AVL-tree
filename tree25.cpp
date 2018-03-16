#include "tree25.h"
#include <string>

using namespace std;


Tree25::Tree25(int _t){  
	root = NULL;  t = _t; 
}
 
void Tree25::traverse(){  
	if (root != NULL) root->traverse(); 
}
 
Tree25Node* Tree25::search(string k) {
	return (root == NULL)? NULL : root->search(k); 
}

void Tree25::insert(string k)
{
    if (root == NULL) {
        root = new Tree25Node(t, true);
        root->keys[0] = k;  // Insert key
        root->n = 1;  // Update number of keys in root
    } else {
        // If root is full, then tree grows in height
        if (root->n == 2*t-1) {
            // Allocate memory for new root
            Tree25Node *s = new Tree25Node(t, false);
 
            // Make old root as child of new root
            s->C[0] = root;
 
            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);
 
            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
 
            // Change root
            root = s;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
}
