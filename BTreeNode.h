#pragma once
#include "BtreeKey.h"
#include "Node.h"
class BTreeNode
{
	BtreeKey *keys; 
	int t;	 // Minimum degree (defines the range for number of keys)
	BTreeNode **C; // An array of child pointers
	int n;	 // Current number of keys
	bool leaf; // Is true when node is leaf. Otherwise false
public:
	BTreeNode(int _t, bool _leaf); // Constructor

	void insertNonFull(int k,node*);

	
	void splitChild(int i, BTreeNode *y);

	void traverse();

	int findKey(int k);

	void remove(int k);
	
	void removeFromLeaf(int idx);
 
    // A function to remove the key present in idx-th position in
    // this node which is a non-leaf node
    void removeFromNonLeaf(int idx);
 
    // A function to get the predecessor of the key- where the key
    // is present in the idx-th position in the node
    int getPred(int idx);
 
    // A function to get the successor of the key- where the key
    // is present in the idx-th position in the node
    int getSucc(int idx);
 
    // A function to fill up the child node present in the idx-th
    // position in the C[] array if that child has less than t-1 keys
    void fill(int idx);
 
    // A function to borrow a key from the C[idx-1]-th node and place
    // it in C[idx]th node
    void borrowFromPrev(int idx);
 
    // A function to borrow a key from the C[idx+1]-th node and place it
    // in C[idx]th node
    void borrowFromNext(int idx);
 
    // A function to merge idx-th child of the node with (idx+1)th child of
    // the node
    void merge(int idx);
	
	BTreeNode *search(int k); 

	friend class BTree;
};

