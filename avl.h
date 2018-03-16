#ifndef	avl_h
#define avl_h
#include <string>

using namespace std;

class AVL {

public:
	AVL();
	~AVL();
	struct Node* newNode(int key);
	int max(int a, int b);
	int height(struct Node *N);
	struct Node *rightRotate(struct Node *y);
	struct Node *leftRotate(struct Node *x);
	int getBalance(struct Node *N);
	struct Node* insert(struct Node* node, int key);
	void inOrder(struct Node *root);



};


#endif