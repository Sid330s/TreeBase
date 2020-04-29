#pragma once
#include "BtreeKey.h"
#include "Node.h"

class BTreeNode {
	BtreeKey *keys; 
	int t;
	BTreeNode **C;
	int n;
	bool leaf;
public:
	BTreeNode(int _t, bool _leaf);
	void insertNonFull(int k,node*);
	void splitChild(int i, BTreeNode *y);
	void traverse();
	int findKey(int k);
	void remove(int k);
	void removeFromLeaf(int idx);
	void removeFromNonLeaf(int idx);
	int getPred(int idx);
	int getSucc(int idx);
	void fill(int idx);
	void borrowFromPrev(int idx);
	void borrowFromNext(int idx);
	void merge(int idx);
	BTreeNode *search(int k); 
	friend class BTree;
};
