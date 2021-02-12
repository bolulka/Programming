#include<iostream>
#include<set>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include<iterator>
#include <iomanip>

using namespace std;

void Print(multiset<string>& set)
{
	for (auto element : set)
	{
		std::cout << element << " ";
	}
}

 static multiset<string> UnionSet(const multiset<string>& set1, const multiset<string>& set2)
{
	auto temp = std::vector<string>(set1.size() + set2.size());
	auto tempEnd = std::set_union(
		set1.begin(), set1.end(),
		set2.begin(), set2.end(),
		temp.begin());
	return std::multiset<string>(temp.begin(), tempEnd);
 }
 multiset<string> static Intersect(const std::multiset<string>& set1, const std::multiset<string>& set2)
 {
	 auto temp = std::vector<string>(std::min(set1.size(), set2.size()));
	 auto tempEnd = std::set_intersection(
		 set1.begin(), set1.end(),
		 set2.begin(), set2.end(),
		 temp.begin());
	 return std::multiset<string>(temp.begin(), tempEnd);
 }

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	multiset<string> aquarium1;
	multiset<string> aquarium2;
	multiset<string> aquarium3;

	ifstream i1file;
	i1file.open("Aquarium1.txt");
	ifstream i2file;
	i2file.open("Aquarium2.txt");
	ifstream i3file;
	i3file.open("Aquarium3.txt");

	string str1;
	while (i1file.good()) {
		getline(i1file, str1, '\n');
		aquarium1.insert(str1);
	}
	string str2;
	while (i2file.good()) {
		getline(i2file, str2, '\n');
		aquarium2.insert(str2);
	}
	string str3;
	while (i3file.good()) {
		getline(i3file, str3, '\n');
		aquarium3.insert(str3);
	}

	/*auto temp = UnionSet(aquarium2, aquarium3);
	auto allFish = UnionSet(temp, aquarium1);
	wcout << "All fish: ";
	Print(allFish);*/

	std::wcout << L"All fish: ";
	Print(aquarium1);
	Print(aquarium2);
	Print(aquarium3);

	std::wcout << endl;
	std::wcout << endl;
	aquarium1.insert(aquarium2.cbegin(), aquarium2.cend());
	aquarium1.insert(aquarium3.cbegin(), aquarium3.cend());
	Print(aquarium1);
	std::wcout << endl;
	std::wcout << endl;

	auto repetitiveFish = Intersect(Intersect(aquarium2, aquarium3),aquarium1);
	std::wcout << L"Unpretentious fish: ";
	Print(repetitiveFish);

	std::wcout << endl;
	system("pause");
}