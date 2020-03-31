#pragma once
#include <string>

using namespace std;
class Taken_Course
{
	

public:
	string course_name;
	string grade;
	void print();
	Taken_Course(string,string);
	~Taken_Course(void);
};

