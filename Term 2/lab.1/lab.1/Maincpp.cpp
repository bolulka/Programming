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
	{ 1, "адзін" },
	{ 1, "один" },
	{ 1, "one" },
	{ 2, "два" },
	{ 2, "two" },
	{ 3, "тры" },
	{ 3, "три" },
	{ 3, "three" },
	{ 4, "чатыры" },
	{ 4, "четыре" },
	{ 4, "four" }
	};

	FindDigit(Poliglot);

	system("pause");
	return 0;

}