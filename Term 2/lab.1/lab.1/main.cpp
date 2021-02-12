#include<iostream>
#include<string>
#include<vector>
#include"Student.h"
#include<map>
#include<iterator>

using namespace std;

void Student::ShowStudent()
{
	
		cout << "ID: " << ID << endl;
		cout << "Name: " << studentName << endl;
		cout << "Lastname: " << studentLastname << endl;
	
}

void FindStudentInVector(vector<Student>& v, int id)
{
	auto count = 0;
	for (auto i = 0; i < v.size(); i++)
	{
		if (id == v[i].ID)
			v[i].ShowStudent();
		else count++;
	}
	if (count == v.size()) cout << "There is no student with this ID." << endl;
}



int main()
{
	Student stud1(123456, "Jack","Rochester");
	Student stud2(123448, "Julia","Armstrong");
	Student stud3(127856, "Jane","Collins");
	Student stud4(127456, "Ficuiliam","Darsi");

	vector<Student> students(4);

	students.push_back(stud1);
	students.push_back(stud2);
	students.push_back(stud3);
	students.push_back(stud4);

	FindStudentInVector(students, 123456);

	cout << endl;

	map<int, Student> ListWithStudents = { 
	{stud1.ID,stud1},
	{123448,stud2},
	{127856,stud3},
	{127456,stud4} };

	
	auto result=ListWithStudents.find(123456);
	//cout << "ID: "<<result->first << endl;
	cout << "Student: " << endl;;
	(result->second).ShowStudent();
	
	system("pause");
}