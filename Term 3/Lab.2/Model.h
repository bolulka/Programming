#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class Visitor;
class Iterator;

class Model {

private:
	int* array; //динамический массив
	int el_count; //элементы в массиве
	int array_size; //размер массива

public:

	friend class ModelIter;
	int sumElements(Model &D);
	wstring toString();
	//void accept(Visitor &);

	Model();
	Model(const Model&);
	Model(Model&&);
	//Model(int size);

	friend Model operator +(Model &l, Model &r)
	{
		Model D;
		if (l.el_count > r.el_count)
		{
			for (int i = 0; i < r.el_count; i++)
			{
				D.PushBack(l.array[i] + r.array[i]);
			}
			for (int i = r.el_count; i < l.el_count; i++)
			{
				D.PushBack(l.array[i]);
			}
		}

		if (l.el_count < r.el_count)
		{
			for (int i = 0; i < l.el_count; i++)
			{
				D.PushBack(r.array[i] + l.array[i]);
			}
			for (int i = l.el_count; i < r.el_count; i++)
			{
				D.PushBack(r.array[i]);
			}
		}

		if (l.el_count == r.el_count)
		{
			for (int i = 0; i < l.el_count; i++)
			{
				D.PushBack(r.array[i] + l.array[i]);
			}
		}
		return D;

	}
	friend Model& operator +=(Model &l, Model &r)
	{
		Model D;
		if (l.el_count > r.el_count) {
			{
				for (int i = 0; i < r.el_count; i++)
				{
					D.PushBack(l.array[i] + r.array[i]);
				}
				for (int i = r.el_count; i < l.el_count; i++)
				{
					D.PushBack(l.array[i]);
				}
				return D;
			}
			for (int i = 0; i < D.el_count; i++)
			{
				l.array[i] = D.array[i];
			}
			return l;
		}
		if (r.el_count > l.el_count) {
			{
				for (int i = 0; i < l.el_count; i++)
				{
					D.PushBack(r.array[i] + l.array[i]);
				}
				for (int i = l.el_count; i < r.el_count; i++)
				{
					D.PushBack(r.array[i]);
				}
				return D;
			}
			for (int i = 0; i < D.el_count; i++)
			{
				l.array[i] = D.array[i];
			}
			return l;
		}
		if (r.el_count == l.el_count)
		{
			for (int i = 0; i < l.el_count; i++)
			{
				l.array[i] = l.array[i] + r.array[i];
			}
		}
		return l;
	}

	 Model& operator =(const Model& rhs)
	{
		if (this == &rhs) { return *this; }
		if (array_size > 0) { delete[] array; }
		el_count = rhs.el_count;
		array_size = rhs.array_size;
		array = new int[array_size];
		for (int i = 0; i < el_count; i++)
		{
			array[i] = rhs.array[i];
		}
		return *this;
	}

	friend istream& operator>>(istream& is, Model& instance)
	{
		int input;
		is >> input;
		instance.PushBack(input);
		return is;
	}

	
	friend ostream& operator<<(std::ostream&, Model&);

	~Model();

	bool IsEmpty();
	void PushFront(int);
	void PopFront();
	void PushBack(int);
	void PopBack();
	void SwapModel(Model&);
	int Front();
	int Back();
	void Clear();
	int GetSize();
};


