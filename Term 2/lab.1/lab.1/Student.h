#pragma once
#include <string>

using namespace std;

class Student
{
public:

	int ID;
	string studentName;
	string studentLastname;
	
	Student() {};
	Student(int id, string name, string lastname)
	{
		ID = id;
		studentName = name;
		studentLastname = lastname;
	}
	~Student() {};

	void ShowStudent();
	/*{
		cout << "ID: " << stud.ID << endl;
		cout << "Name: " << stud.studentName << endl;
		cout << "Lastname: " << stud.studentLastname << endl;
	}*/
};
