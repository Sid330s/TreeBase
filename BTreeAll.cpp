#include "BTreeAll.h"
#include <iostream>
using namespace std;

BTree::BTree() { 
	root = NULL;
}

void BTree::traverse() { 
	if (root != NULL) root->traverse();
}

node* BTree::search(int k) { 
	if ((root->search(k) == NULL) || (root == NULL))
		return NULL;
	else {
		BTreeNode* rec_found = root->search(k);
		for(int i=0;i<rec_found->n;i++) {
			if (k==rec_found->keys[i].roll_no)
				return rec_found->keys[i].record;
		}
	}
}

void BTree::insert(int k,node* rec) {
	if (root == NULL) {
		root = new BTreeNode(t, true);
		root->keys[0].roll_no = k; 
		root->keys[0].record = rec;
		root->n = 1; 
	} else {
		if (root->n == 2*t-1) {
			BTreeNode *s = new BTreeNode(t, false);
			s->C[0] = root;
			s->splitChild(0, root);
			int i = 0;
			if (s->keys[0].roll_no < k) i++;
			s->C[i]->insertNonFull(k,rec);
			root = s;
		} else  root->insertNonFull(k,rec);
	}
}

void BTree::set_order(int _t) {
	t= _t;
}

void BTree::remove(int k) {
	if (!root) {
		cout << "The tree is empty\n";
		return;
	}

	root->remove(k);

	if (root->n==0) {
		BTreeNode *tmp = root;
		if (root->leaf) root = NULL;
		else root = root->C[0];
		delete tmp;
	}
	return;
}
