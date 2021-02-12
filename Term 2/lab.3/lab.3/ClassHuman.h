#pragma once
#include <algorithm>
#include <string>
#include <sstream>
#include <io.h>
#include <fcntl.h>
#include <iostream>


using namespace std;

class Human
{
private:
	wstring name;
	wstring surname;
	wstring patronymic;
public:
	void SetData();
	void ShowData();
	wstring GetSurname();
	~Human() {};
};


void Human::ShowData()
{
	wcout << L" " << name[0] << L". " << patronymic[0] << L". " << surname << endl;
}

void Human::SetData()
{
	wcin >> surname;
	wcin >> name;
	wcin >> patronymic;
}

wstring Human::GetSurname()
{
	return surname;
}