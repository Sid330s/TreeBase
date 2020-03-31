#include "BTreeNode.h"
#include <iostream>
using namespace std;


BTreeNode::BTreeNode(int t1, bool leaf1)
{
	
	t = t1;
	leaf = leaf1;

	keys = new BtreeKey[2*t-1];
	C = new BTreeNode *[2*t];

	n = 0;
}


void BTreeNode::traverse()
{
	int i;
	for (i = 0; i < n; i++)
	{

		if (leaf == false)
			C[i]->traverse();
		cout << " " << keys[i].roll_no;
	}


	if (leaf == false)
		C[i]->traverse();
}


BTreeNode *BTreeNode::search(int k)
{
	int i = 0;
	while (i < n && k > keys[i].roll_no)
		i++;

	if (keys[i].roll_no == k)
		return this;

	if (leaf == true)
		return NULL;

	return C[i]->search(k);
}

void BTreeNode::insertNonFull(int k,node* rec)
{
	int i = n-1;

	if (leaf == true)
	{
		while (i >= 0 && keys[i].roll_no > k)
		{
			keys[i+1] = keys[i];
			i--;
		}
		keys[i+1].roll_no = k;
		keys[i+1].record = rec;
		n = n+1;
	}
	else 
	{
		
		while (i >= 0 && keys[i].roll_no > k)
			i--;

		
		if (C[i+1]->n == 2*t-1)
		{
			splitChild(i+1, C[i+1]);

			if (keys[i+1].roll_no < k)
				i++;
		}
		C[i+1]->insertNonFull(k,rec);
	}
}

void BTreeNode::splitChild(int i, BTreeNode *y)
{

	BTreeNode *z = new BTreeNode(y->t, y->leaf);
	z->n = t - 1;

	for (int j = 0; j < t-1; j++)
		z->keys[j] = y->keys[j+t];

	if (y->leaf == false)
	{
		for (int j = 0; j < t; j++)
			z->C[j] = y->C[j+t];
	}

	y->n = t - 1;

	
	for (int j = n; j >= i+1; j--)
		C[j+1] = C[j];

	C[i+1] = z;

	for (int j = n-1; j >= i; j--)
		keys[j+1] = keys[j];

	keys[i] = y->keys[t-1];

	n = n + 1;
}

int BTreeNode::findKey(int k)
{
    int idx=0;
	while (idx<n && keys[idx].roll_no < k)
        ++idx;
    return idx;
}
 
// A function to remove the key k from the sub-tree rooted with this node
void BTreeNode::remove(int k)
{
    int idx = findKey(k);
 
    // The key to be removed is present in this node
	if (idx < n && keys[idx].roll_no == k)
    {
 
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {
 
        // If this node is a leaf node, then the key is not present in tree
        if (leaf)
        {
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }
 
        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ( (idx==n)? true : false );
 
        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (C[idx]->n < t)
            fill(idx);
 
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > n)
            C[idx-1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}
 
// A function to remove the idx-th key from this node - which is a leaf node
void BTreeNode::removeFromLeaf (int idx)
{
 
    // Move all the keys after the idx-th pos one place backward
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];
 
    // Reduce the count of keys
    n--;
 
    return;
}
 
// A function to remove the idx-th key from this node - which is a non-leaf node
void BTreeNode::removeFromNonLeaf(int idx)
{
 
	int k = keys[idx].roll_no;
 
    // If the child that precedes k (C[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (C[idx]->n >= t)
    {
        int pred = getPred(idx);
		keys[idx].roll_no = pred;
        C[idx]->remove(pred);
    }
 
    // If the child C[idx] has less that t keys, examine C[idx+1].
    // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
    // the subtree rooted at C[idx+1]
    // Replace k by succ
    // Recursively delete succ in C[idx+1]
    else if  (C[idx+1]->n >= t)
    {
        int succ = getSucc(idx);
		keys[idx].roll_no = succ;
        C[idx+1]->remove(succ);
    }
 
    // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
    // into C[idx]
    // Now C[idx] contains 2t-1 keys
    // Free C[idx+1] and recursively delete k from C[idx]
    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}
 
// A function to get predecessor of keys[idx]
int BTreeNode::getPred(int idx)
{
    // Keep moving to the right most node until we reach a leaf
    BTreeNode *cur=C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
 
    // Return the last key of the leaf
	return cur->keys[cur->n-1].roll_no;
}
 
int BTreeNode::getSucc(int idx)
{
 
    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
    BTreeNode *cur = C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];
 
    // Return the first key of the leaf
	return cur->keys[0].roll_no;
}
 
// A function to fill child C[idx] which has less than t-1 keys
void BTreeNode::fill(int idx)
{
 
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (idx!=0 && C[idx-1]->n>=t)
        borrowFromPrev(idx);
 
    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
    // from that child
    else if (idx!=n && C[idx+1]->n>=t)
        borrowFromNext(idx);
 
    // Merge C[idx] with its sibling
    // If C[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}
 
// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
void BTreeNode::borrowFromPrev(int idx)
{
 
    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx-1];
 
    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key
 
    // Moving all key in C[idx] one step ahead
    for (int i=child->n-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];
 
    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }
 
    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = keys[idx-1];
 
    // Moving sibling's last child as C[idx]'s first child
    if (!leaf)
        child->C[0] = sibling->C[sibling->n];
 
    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    keys[idx-1] = sibling->keys[sibling->n-1];
 
    child->n += 1;
    sibling->n -= 1;
 
    return;
}
 
// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
void BTreeNode::borrowFromNext(int idx)
{
 
    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx+1];
 
    // keys[idx] is inserted as the last key in C[idx]
    child->keys[(child->n)] = keys[idx];
 
    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!(child->leaf))
        child->C[(child->n)+1] = sibling->C[0];
 
    //The first key from sibling is inserted into keys[idx]
    keys[idx] = sibling->keys[0];
 
    // Moving all keys in sibling one step behind
    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];
 
    // Moving the child pointers one step behind
    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }
 
    // Increasing and decreasing the key count of C[idx] and C[idx+1]
    // respectively
    child->n += 1;
    sibling->n -= 1;
 
    return;
}
 
// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void BTreeNode::merge(int idx)
{
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx+1];
 
    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->keys[t-1] = keys[idx];
 
    // Copying the keys from C[idx+1] to C[idx] at the end
    for (int i=0; i<sibling->n; ++i)
        child->keys[i+t] = sibling->keys[i];
 
    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->n; ++i)
            child->C[i+t] = sibling->C[i];
    }
 
    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to C[idx]
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];
 
    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i=idx+2; i<=n; ++i)
        C[i-1] = C[i];
 
    // Updating the key count of child and the current node
    child->n += sibling->n+1;
    n--;
 
    // Freeing the memory occupied by sibling
    delete(sibling);
    return;
}
