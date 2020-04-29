#pragma once
#include <vector>
#include <string>
#include "Taken_Course.h"
using namespace std;
class Student
{
	int roll_number;
	

public:
	string name;
	vector<Taken_Course*> courses_taken;
	void print();
	int get_roll_number();
	Student(int,string,vector<Taken_Course*>);
	~Student(void);
};

