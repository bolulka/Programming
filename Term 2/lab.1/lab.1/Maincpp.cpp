#include <iostream>
#include <map>
#include <string>

using namespace std;

void FindDigit(multimap<int, string> &Poliglot)
{
	int n;
	cout << "Enter digit : ";
	cin >> n;
	auto iterator = Poliglot.lower_bound(n);
	auto last_iterator= Poliglot.upper_bound(n);
	if (iterator !=Poliglot.end())
		for (iterator; iterator != last_iterator; ++iterator)
			cout << iterator->second << endl;
	else
		cout << "Not found " << endl;
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");

	multimap<int, string> Poliglot = {
	{ 1, "����" },
	{ 1, "����" },
	{ 1, "one" },
	{ 2, "���" },
	{ 2, "two" },
	{ 3, "���" },
	{ 3, "���" },
	{ 3, "three" },
	{ 4, "������" },
	{ 4, "������" },
	{ 4, "four" }
	};

	FindDigit(Poliglot);

	system("pause");
	return 0;

}