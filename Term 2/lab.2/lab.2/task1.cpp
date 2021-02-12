#include<iostream>
#include<set>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include<iterator>
#include <iomanip>
//#include <io.h>
//#include <fcntl.h>
//#include <locale>


using namespace std;

static void PrintLine()
{
	std::wcout << std::endl;
}
template<typename T>
static void Print(const T& collection)
{
	for (auto element : collection)
	{
		std::cout << element << " ";
	}
	PrintLine();
}


template<typename T> std::set<T>
	static Intersect(const std::set<T>& set1, const std::set<T>& set2)
	{
		auto temp = std::vector<T>(std::min(set1.size(), set2.size()));
		auto tempEnd = std::set_intersection(
			set1.begin(), set1.end(),
			set2.begin(), set2.end(),
			temp.begin());
		return std::set<T>(temp.begin(), tempEnd);
	}

template<typename T> std::set<T>
	static SymmetricDifference(const std::set<T>& set1, const std::set<T>& set2)
		{
			auto temp = std::vector<T>(set1.size()+set2.size());
			auto tempEnd = std::set_symmetric_difference(
				set1.begin(), set1.end(),
				set2.begin(), set2.end(),
				temp.begin());
			return std::set<T>(temp.begin(), tempEnd);
		}

template<typename T> std::set<T>
	static Difference(const std::set<T>& set1, const std::set<T>& set2)
		{
			auto temp = std::vector<T>(set1.size());
			auto tempEnd = std::set_difference(
				set1.begin(), set1.end(),
				set2.begin(), set2.end(),
				temp.begin());
			return std::set<T>(temp.begin(), tempEnd);
		}

	
int main() {

	setlocale(LC_ALL, "RUSSIAN");

	set<string> lake1;
	set<string> lake2;
	set<string> lake3;

	ifstream i1file;
	i1file.open("C:\\Users\\Julia\\source\\repos\\Lab.2\\lake1.txt");
	ifstream i2file;
	i2file.open("C:\\Users\\Julia\\source\\repos\\Lab.2\\lake2.txt");
	ifstream i3file;
	i3file.open("C:\\Users\\Julia\\source\\repos\\Lab.2\\lake3.txt");

	string str1;
	while (i1file.good()) 
	{
		getline(i1file, str1, '\n');
		lake1.insert(str1);
	}
	string str2;
	while (i2file.good())
	{
		getline(i2file, str2, '\n');
		lake2.insert(str2);
	}
	string str3;
	while (i3file.good())
	{
		getline(i3file, str3, '\n');
		lake3.insert(str3);
	}

	wcout << "Fish from the first lake:  " << endl;
	Print(lake1);

	wcout << "Fish from the second lake:  " << endl;
	Print(lake2);

	wcout << "Fish from the third lake:  " << endl;
	Print(lake3);

	auto idealFish = Intersect(lake3, Intersect(lake1, lake2));
	wcout << "Unpretentious fish: ";
	Print(idealFish);

	auto specislFish = SymmetricDifference(Difference(lake3,lake2), SymmetricDifference(lake1, lake2));
	wcout << "Pretentious fish: ";
	Print(specislFish);

	auto special1lakeFish = Difference(Difference(lake1, lake3), lake2);
	wcout << "Pretentious fish from the first lake: ";
	Print(special1lakeFish);

	system("pause");
}
