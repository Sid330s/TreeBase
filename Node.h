#pragma once
#include "Student.h"

struct node
{
	node *next;
	node *prev;
	Student * student;
};