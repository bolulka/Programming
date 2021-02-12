#pragma once
#include "stdafx.h"
#include <ostream>
#include <istream>
#include <string>

class Visitor;
//class Iterator;

class Iterator {                                  // Iterator
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual bool isDone() = 0;
	virtual int currentItem() const = 0;
protected:
	Iterator() {};
};


class Model
{
	int* array;
	int array_size = 0;
	int el_count = 0;

public:

	friend class DequeIter;
	int sumElements(Model &D);
	std::wstring to_wstring(/*int position*/);

	Model();

	Model(int array_size);

	Model(Model&& other);

	Model(const Model& other);

	~Model();

	void PushBack(const int& instance);

	void PushFront(const int& instance);

	void PopFront();

	void PopBack();

	void Clear();

	bool IsEmpty();

	int Size();

	int Front();

	int Back();

	//std::wstring to_String();

	void Swap(int first_pos, int second_pos);

	bool operator==(const Model&);

	bool operator!=(const Model&);

	Model& operator=(const Model& rhs);

	Model operator+(Model const&) const;

	Model& operator+=(const Model&);

	friend std::ostream& operator<<(std::ostream&, Model&);

	friend std::istream& operator>>(std::istream&, Model&);

};

class DequeIter : public Iterator
{
private:

	Model* dec;
	int index;

public:

	DequeIter(Model *d)
	{
		dec = d;
	}

	inline virtual int currentItem() const;
	inline virtual void first();
	inline virtual void next();
	inline virtual bool isDone();
};

void  DequeIter::first()
{
	index = 0;
}
void DequeIter::next()
{
	index++;
}
bool DequeIter::isDone()
{
	return index == dec->el_count;
}
int DequeIter::currentItem() const
{
	return dec->array[index];
}


