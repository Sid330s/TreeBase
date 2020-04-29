#include "Sorted_Doubly_Linked_List.h"
#include <iostream>
using namespace std;

Sorted_Doubly_Linked_List::Sorted_Doubly_Linked_List(void) {
	head = NULL, tail = NULL, p = NULL, r = NULL, np = NULL;
	c=0;
}

node* Sorted_Doubly_Linked_List::create(Student *s1) {
	np = new node;
	np->student = s1;
	np->next = NULL;
	np->prev = NULL;
	if (c == 0) {
		tail = np;
		head = np;
		p = head;
		p->next = NULL;
		p->prev = NULL;
		c++;
	} else {
		p = head;
		r = p;
		if (np->student->get_roll_number() < p->student->get_roll_number()) {
			np->next = p;
			p->prev = np;
			np->prev = NULL;
			head = np;
			p = head;
			do {
				p = p->next;
			} while (p->next != NULL);
			tail = p;
		} else if (np->student->get_roll_number() > p->student->get_roll_number()) {
			while (p != NULL && np->student->get_roll_number() > p->student->get_roll_number()) {
				r = p;
				p = p->next;
				if (p == NULL) {
					r->next = np;
					np->prev = r;
					np->next = NULL;
					tail = np;
					break;
				} else if (np->student->get_roll_number() < p->student->get_roll_number()) {
					r->next = np;
					np->prev = r;
					np->next = p;
					p->prev = np;
					if (p->next != NULL) {
						do {
							p = p->next;
						} while (p->next !=NULL);
					}
					tail = p;
					break;
				}
			}
		}
	}
	return np;
}

void Sorted_Doubly_Linked_List::descending() {
	node *t = tail;
	while (t != NULL) {
		t->student->print();
		t = t->prev;
	}
	cout<<endl;
}

void Sorted_Doubly_Linked_List::ascending() {
	node *t = head;
	while (t != NULL) {
		t->student->print();
		t = t->next;
	}
	cout<<endl;
}

void Sorted_Doubly_Linked_List::delete_student(int roll) {
	node *t = head;
	if (head == NULL) {
		cout<<"There are no students\n";
		return;
	}
	while (t->student->get_roll_number() != roll) {
		t = t->next;
		if (t==NULL)
		break;
	}
	if(t==NULL) {
		cout<<"There are no student with this Roll No.\n";
		return;
	}
	if (t->student->get_roll_number() == roll) {
		deleteNode(&head,t);
		cout<<"Student Record Deleted\n";
	}
}

void Sorted_Doubly_Linked_List::deleteNode(struct node **head_ref, struct node *del) {
	if(*head_ref == NULL || del == NULL) return;
	if(*head_ref == del) *head_ref = del->next;
	if(del->next != NULL) del->next->prev = del->prev;
	if(del->prev != NULL) del->prev->next = del->next;     
	free(del);
	return;
}     

Sorted_Doubly_Linked_List::~Sorted_Doubly_Linked_List(void) {
}
