#include "Student.h"
#include <iostream>

Student::Student(int roll,string student_name,vector<Taken_Course*> courses)
{
	roll_number = roll;
	name = student_name;
	courses_taken = courses;
}
int Student::get_roll_number()
{
	return roll_number;
}
void Student::print()
{
	cout<<"Student Name : ";
	cout<<name;
	cout<<"  <---->  Roll Number : ";
	cout<<roll_number<<endl;

	cout<<"Course Name  <---->  Grade\n";
	
	for(Taken_Course* i : courses_taken) 
		i->print();

}

Student::~Student(void)
{
}
