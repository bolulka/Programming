#include <iostream>
#include <string>
#include "Model.h"

using namespace std;

int main()
{

	Model dec1;

	dec1.PushFront(12);
	dec1.PushFront(32);
	dec1.PushFront(20);

	dec1.PushBack(13);
	dec1.PushBack(33);
	dec1.PushBack(21);

	cout << "Dec1: " << dec1;
	cout << endl;
	//cout << dec1.toString();


	dec1.PopBack();
	dec1.PopFront();

	cout << "Dec1 after PopFront & PopBack: " << dec1;
	cout << endl;

	Model dec2;

	dec2.PushFront(3);
	dec2.PushFront(5);
	dec2.PushFront(7);

	dec2.PushBack(9);
	dec2.PushBack(11);
	dec2.PushBack(13);

	cout << "Dec2: " << dec2;
	cout << endl;

	Model dec3;
	dec3 = dec1 + dec2;
	cout << "Dec1 + Dec2: " << dec3;
	cout << endl;

	cout << "Front: " << dec3.Front() << '\n';
	cout << "Back: " << dec3.Back() << '\n';
	cout << "Size: " << dec3.GetSize() << '\n';
	cout << "Sum of elements: " << dec3.sumElements(dec1) << '\n';

	system("pause");
}