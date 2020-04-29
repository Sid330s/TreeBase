#pragma once
#include "BTreeNode.h"
#include "Node.h"
class BTree
{
	BTreeNode *root; 
	int t; // Minimum degree
public:
	
	BTree();
	void set_order(int);
	void traverse();
	node* search(int k);
	void insert(int k,node*);
	// The main function that removes a new key in thie B-Tree
    void remove(int k);
};