#include <iostream>
#include "Student.h"
#include "Taken_Course.h"
#include "Sorted_Doubly_Linked_List.h"
#include "Node.h"
#include "BTreeAll.h"
#include "BtreeKey.h"
#include "BTreeNode.h"
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include <stdio.h>

// Main.cpp BtreeAll.cpp BTreeNode.cpp Sorted_Doubly_Linked_List.cpp Student.cpp Taken_Course.cpp -o new

using namespace std;

int main()
{
	int order_of_btree;
	BTree t;
	Sorted_Doubly_Linked_List sdll;
	int ch1;
	cout<<"      <---------------    CSE_SY_B : Group 2    -------------->    \n\n";
	cout<<"	     <---------   DataStructures || Course Project    ------->    \n\n";
	cout<<"	     <---------------------   TreeBase   -------------------->    \n\n";
	cout<<"                1 : Load Database from an existing file            \n\n";
	cout<<"                2 : Create a new Database\n\nEnter Option :        \n\n";
	cin>>ch1;
	if (ch1 == 1)
	{
		ifstream infile("student_data.txt");
		string rder;
		getline(infile, rder);
		int order = stoi(rder);
		order_of_btree = order;
		string line;
		t.set_order(order);
		while (getline(infile, line))
		{
			vector<Taken_Course*> courses;
			istringstream iss(line);
			vector<string> words;
			while (getline(iss, line, ' '))
				words.push_back(line);
			int roll_number=stoi(words[0]);
			string name = words[1]+ " " + words[2];

			for (int i=3;i<words.size();i++)
			{
				string course_name = words[i];
				string grade = words[i+1];
				i+=1;
				Taken_Course* c = new Taken_Course(course_name,grade);
				courses.push_back(c);
			}
			Student* s = new Student(roll_number,name,courses);
			node* n;
			n = sdll.create(s);
			t.insert(roll_number,n);

		}

		infile.close();

		getch();

	}
	else
	{
		// create you own database
		int order;
		cout<<"Set the order of B-tree : ";
		cin>>order;
		order_of_btree = order;
		t.set_order(order);
		int choice = 1;
		while (choice == 1)
		{
			cout<<"RollNo Name Surname Subject1 Grade1 Subject2 Grade2 Subject3 Grade3 Subject4 Grade4\n";
			cout<<"Enter the record in the above mentioned format : \n";

			char inputarr[200];
			int index = 0;
			char input;
			cin.ignore();
			do {
				input=getchar();
				inputarr[index++] = input;
			} while (input != '\n');
			inputarr[index] = '\0';

			string record(inputarr);
			//cout<<record;
			istringstream iss(record);
			vector<Taken_Course*> courses;
			vector<string> words;
			while (getline(iss, record, ' '))
				words.push_back(record);
			int roll_number=stoi(words[0]);
			string name = words[1]+ " " + words[2];

			for (int i=3;i<words.size();i++)
			{
				string course_name = words[i];
				string grade = words[i+1];
				i+=1;
				Taken_Course* c = new Taken_Course(course_name,grade);
				courses.push_back(c);
			}
			Student* s = new Student(roll_number,name,courses);
			node* n;
			n = sdll.create(s);
			t.insert(roll_number,n);

			cout<<"\nDo You Want to Insert Another Record ? (Yes == 1,No == 0) : ";
			cin>>choice;
		}

	}
	while (true)
	{
		cout<<"	     <---------   Operations    ------->    \n\n"; 
		cout<<"		1 : Create Record"<<endl; 
		cout<<"		2 : Read Record"<<endl; 
		cout<<"		3 : Delete Record"<<endl; 
		cout<<"		4 : Update Record"<<endl; 
		cout<<"		5 : View All Records"<<endl; 
		cout<<"		6 : Records in a Range(Ascending)"<<endl; 
		cout<<"		7 : Records in a Range(Descending)"<<endl; 
		cout<<"		8 : Save to File"<<endl<<endl; 
		cout<<"	Enter Your Option : ";
		cin>>ch1;
		if (ch1 == 1){

			cout<<"RollNo Name Surname Subject1 Grade1 Subject2 Grade2 Subject3 Grade3 Subject4 Grade4\n";
			cout<<"Enter the record in the above mentioned format : \n";
			char inputarr[200];
			int index = 0;
			char input;
			cin.ignore();
			do {
				input=getchar();
				inputarr[index++] = input;
			} while (input != '\n');
			inputarr[index] = '\0';
			string record(inputarr);
			istringstream iss(record);
			vector<Taken_Course*> courses;
			vector<string> words;
			while (getline(iss, record, ' '))
				words.push_back(record);
			int roll_number=stoi(words[0]);
			string name = words[1]+ " " + words[2];

			for (int i=3;i<words.size();i++)
			{
				string course_name = words[i];
				string grade = words[i+1];
				i+=1;
				Taken_Course* c = new Taken_Course(course_name,grade);
				courses.push_back(c);
			}
			Student* s = new Student(roll_number,name,courses);
			node* n;
			n = sdll.create(s);
			t.insert(roll_number,n);
		}
		else if (ch1 == 5)
		{
			sdll.ascending();
		}
		else if (ch1 == 2)
		{
			int r;
			cout<<"Enter the Roll Number of the student : ";
			cin>>r;
			(t.search(r) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
			if (t.search(r) != NULL)
			{
				node* found_record = t.search(r);
				found_record->student->print();
			}
		}
		else if (ch1==3)
		{
			int r;
			cout<<"Enter the Roll Number of the student : ";
			cin>>r;
			t.remove(r);
			sdll.delete_student(r);
		}
		else if (ch1==6)
		{
			int r1;
			cout<<"Enter Starting RollNo : ";
			cin>>r1;
			int r2;
			cout<<"Enter Ending RollNo : ";
			cin>>r2;
			cout<<endl;
			for (int i=r1;i<=r2;i++)
			{
				if (t.search(i) != NULL)
				{
					node* found_record = t.search(i);
					found_record->student->print();
				}
			}
		}
		else if (ch1==7)
		{
			int r1;
			cout<<"Enter Starting RollNo : ";
			cin>>r1;
			int r2;
			cout<<"Enter Ending RollNo : ";
			cin>>r2;
			cout<<endl;
			for (int i=r2;i>=r1;i--)
			{
				if (t.search(i) != NULL)
				{
					node* found_record = t.search(i);
					found_record->student->print();
				}
			}
		}
		else if(ch1==4)
		{
			int r;
			cout<<"Enter the Roll Number of the student : ";
			cin>>r;
			(t.search(r) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
			if (t.search(r) != NULL)
			{
				node* found_record = t.search(r);
				found_record->student->print();
			}

			cout<<"RollNo Name Surname subject1 grade1 subject2 grade2 subject3 grade3 subject4 grade4\n";
			cout<<"Enter the record in the above mentioned format : \n";
			char inputarr[200];
			int index = 0;
			char input;
			cin.ignore();
			do {
				input=getchar();
				inputarr[index++] = input;
			} while (input != '\n');
			inputarr[index] = '\0';
			string record(inputarr);
			//cout<<record;
			istringstream iss(record);
			vector<Taken_Course*> courses;
			vector<string> words;
			while (getline(iss, record, ' '))
				words.push_back(record);
			int roll_number=r;
			string name = words[0]+ " " + words[1];

			for (int i=2;i<words.size();i++)
			{
				string course_name = words[i];
				string grade = words[i+1];
				i+=1;
				Taken_Course* c = new Taken_Course(course_name,grade);
				courses.push_back(c);
			}
			Student* s = new Student(roll_number,name,courses);
			node* n;

			t.remove(r);
			sdll.delete_student(r);

			n = sdll.create(s);
			t.insert(roll_number,n);
		}
		else if (ch1==8)
		{
			ofstream fout("student_data.txt");
			fout<<order_of_btree<<endl;
			node* t = sdll.head;
			string record = "";
			while(t!=NULL)
			{
				fout<<t->student->get_roll_number()<<" "<<t->student->name<<" ";
				for(Taken_Course* i : t->student->courses_taken)
				{
					fout<<i->course_name<<" "<<i->grade;
				}
				fout<<endl;
				t=t->next;
			}
		}
		else
		{
			cout<<"Wrong Option Selected \n";
		}
	}
	cout<<endl;
	return 0;
}
