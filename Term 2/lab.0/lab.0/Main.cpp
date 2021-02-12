#include<iostream>
#include<list>
#include<algorithm>
#include<iterator>

using namespace std;

int const QuantityOfSolders = 1000;
int const Period = 35;

void FindNumber(list<int>& list)
{
	auto iterator = list.begin();

	if(list.size()>1)
	{
		for (int i = 0; i < Period; i++)
		{
			list.push_back(*iterator);
			list.pop_front();
			iterator = list.begin();
		}
		list.pop_front();
		FindNumber(list);
	}
	else
	{
		cout << "Survives: "<< list.front() <<endl;
	}

}


int main() {

	list<int> ListOfSolders;
	for (int i = 1; i <= QuantityOfSolders; ++i)
		ListOfSolders.push_back(i);

	cout << "Among " << QuantityOfSolders << " solders, at the death of each " << Period<< endl;
	FindNumber(ListOfSolders);

	system("pause");
}
