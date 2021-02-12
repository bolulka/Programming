#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <io.h>
#include <map>
#include <fcntl.h>
#include "ClassHuman.h"

using namespace std;

const int Count = 3;

void ShowMap(multimap<wstring, Human>& People)
{
	int i = 0;
	for (auto it = People.begin(); it != People.end(); ++it)
	{
		wcout << ++i << endl;
		it->second.ShowData();
	}
}

multimap<wstring, Human> CreateList(int count)
{
	wcout << "Input info (in format: Surname, Name, Patronymic) " << endl;
	multimap<wstring, Human> People;
	for (int i = 0; i < count; i++)
	{
		Human m;
		m.SetData();
		People.insert(pair<wstring, Human>(m.GetSurname(), m));
	}
	return People;
}

void FindPerson(multimap<wstring, Human>& People)
{
	wstring surname;
	wcout << "Enter surname : ";
	wcin >> surname;
	auto iterator = People.find(surname);
	if (iterator != People.end())
		for (iterator; iterator != People.upper_bound(surname); ++iterator)
			iterator->second.ShowData();
	else
		wcout << L"Not found " << endl;
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	multimap<wstring, Human> People = CreateList(Count);
	ShowMap(People);
	FindPerson(People);
	system("pause");
}