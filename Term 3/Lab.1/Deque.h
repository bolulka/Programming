#pragma once
#include "stdafx.h"
#include <ostream>
#include <istream>
#include <string>
//#include "Deque.cpp"

class Deque
{
	int* array;
	int array_size = 0;
	int el_count = 0;

public:

	class Iterator
	{
	public:
		Iterator(const Deque*, int);
		const int& operator*() const;
		Iterator& operator++();
		bool operator!=(const Iterator&) const;
		bool operator==(const Iterator&) const;
	private:
		const Deque* iterated_dec;
		int index = -1;
	};

	Iterator begin() const;

	Iterator end() const;

	Deque();


	Deque(int array_size);

	Deque(Deque&& other);

	Deque(const Deque& other);

	~Deque();

	void PushBack(const int& instance);

	void PushFront(const int& instance);

	void PopFront();

	void PopBack();

	void Clear();

	bool IsEmpty();

	int Size();

	int Front();

	int Back();

	std::wstring to_String();

	void Swap(int first_pos, int second_pos);

	bool operator==(const Deque&);

	bool operator!=(const Deque&);

	Deque& operator=(const Deque& rhs);

	int& operator[](int);

	int operator[](int) const;

	Deque operator+(Deque const&) const;

	Deque& operator+=(const Deque&);

	friend std::ostream& operator<<(std::ostream&, Deque&);//DELETE, FRIEND NOT NECESSARY

	friend std::istream& operator>>(std::istream&, Deque&);//DELETE, FRIEND NOT NECESSARY

};