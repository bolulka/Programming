#include <algorithm> 
#include <string> 
#include <sstream> 
#include <io.h> 
#include <fcntl.h> 
#include <iostream> 
#include <map> 

using namespace std;

class Human
{
private:

	wstring name;
	wstring surname;
	wstring patronymic;

public:

	void SetData()
	{
		wcout << "Input person's data(in format surname,name,patronymic) : " << endl;
		wcin>> surname;
		wcin>> name;
		wcin>> patronymic;
	}

	void ShowHuman()
	{
		wcout << name[0]<< L". " << patronymic[0]<< L". "<< surname << endl;
	}

	wstring GetSurname()
	{
		return surname;
	}
};

const int Count = 3;

map <wstring, Human> CreateMap(int count)
{
	map <wstring, Human> people;
	for (int i = 0; i < count; i++)
	{
		Human person;
		person.SetData();
		people.insert({ person.GetSurname(), person });
	}
	return people;
}

void ShowMap(map <wstring, Human> & people)
{
	for (auto pair : people)
	{
		pair.second.ShowHuman();
	}
}

void ChooseThePerson(map <wstring, Human> & people)
{
	wstring surname;
	wcout << L"Input person's surname : " << endl;
	wcin >> surname;
	auto iterator = people.find(surname);
	if (iterator != people.end())
		for (iterator; iterator != people.upper_bound(surname); ++iterator)
			iterator->second.ShowHuman();
	else
		wcout << L"Unknown" << endl;
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	map <wstring, Human> People = CreateMap(Count);
	ShowMap(People);
	ChooseThePerson(People);
	system("pause");
}