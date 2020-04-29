#pragma once
#include "BTreeNode.h"
#include "Node.h"

class BTree {
	BTreeNode *root; 
	int t;
	
public:	
	BTree();
	void set_order(int);
	void traverse();
	node* search(int k);
	void insert(int k,node*);
	void remove(int k);
};
