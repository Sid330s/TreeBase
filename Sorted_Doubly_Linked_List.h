#pragma once
#include "Student.h"
#include "node.h"

class Sorted_Doubly_Linked_List {
	int c;
	public:
	node *head ;
	node *tail ; 
	node *p ;
	node *r ;
	node *np ;
	node *create(Student* s1); 
	void descending();
	void ascending();
	Sorted_Doubly_Linked_List(void);
	~Sorted_Doubly_Linked_List(void);
	void deleteNode(struct node **head_ref, struct node *del);
	void delete_student(int roll);
};
