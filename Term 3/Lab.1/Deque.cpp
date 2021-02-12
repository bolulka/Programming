#include "Deque.h"
#include "stdafx.h"
#include <utility>
#include <ostream>
#include <istream>
#include <iostream>
#include <algorithm>

Deque::Deque() : array_size(0), el_count(0) { }

Deque::Deque(Deque&& other) : array_size(0), el_count(0)
{
	std::swap(array, other.array);
	std::swap(array_size, other.array_size);
	std::swap(el_count, other.el_count);
}

Deque::Deque(const Deque& other) : array_size(0), el_count(0)
{
	for (auto x : other) { PushBack(x); }
}

Deque::~Deque()
{
	delete[] array;
	array_size = 0;
	el_count = 0;
}

void Deque::PushBack(const int& instance)
{
	if (el_count == array_size)
	{
		array_size = array_size * 2 + 1;
		int* temporary_array = new int[array_size];
		for (int i = 0; i < el_count; i++)
		{
			temporary_array[i] = array[i];
		}
		std::swap(temporary_array, array);
		delete temporary_array;
	}
	array[el_count] = instance;
	el_count++;
}

void Deque::PushFront(const int& instance)
{
	if (el_count == array_size)
	{
		array_size = array_size * 2 + 1;
		int* temporary_array = new int[array_size];
		for (int i = 1; i < el_count + 1; i++)
		{
			temporary_array[i] = array[i - 1];
		}
		std::swap(temporary_array, array);
		delete temporary_array;
	}
	else
	{
		for (int i = el_count; i >= 0; i--)
		{
			array[i + 1] = array[i];
		}
	}
	array[0] = instance;
	el_count++;
}

void Deque::PopBack()
{
	el_count--;
}

void Deque::PopFront()
{
	for (int i = 0; i < el_count; i++)
	{
		array[i] = array[i + 1];
	}
	el_count--;
}

void Deque::Clear()
{
	el_count = 0;
	array_size = 0;
}

bool Deque::IsEmpty()
{
	if (el_count == 0)
		return true;
	else return false;
}

int	Deque::Size()
{
	return el_count;
}

int Deque::Front()
{
	return array[0];
}

int Deque::Back()
{
	return array[el_count - 1];
}

void Deque::Swap(int first_pos, int second_pos)
{
	if (el_count == 1 || el_count==0) return;
	if ((first_pos > el_count-1) || (second_pos > el_count-1)) return;
	//cout << "Mistake"; return ;
	int el1;
	int el2;
	el1 = array[first_pos];
	el2 = array[second_pos];

	array[first_pos] = el2;
	array[second_pos] = el1;

}

std::wstring Deque::to_String()
{
	std::wstring str;
	for (int i = 0; i < el_count; i++)
	{
		str += std::to_wstring(array[i])+= L" ";
	}
	return str;
};

bool Deque::operator==(const Deque& rhs)
{
	if (el_count != rhs.el_count) { return false; }
	std::sort(array, array + el_count);
	std::sort(rhs.array, rhs.array + el_count);
	for (int i = 0; i < el_count; i++)
	{
		if (array[i] != rhs.array[i]) { return false; }
	}
	return true;
}

bool Deque::operator!=(const Deque& rhs)
{
	return !(*this == rhs);
}

Deque& Deque::operator=(const Deque& rhs)
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

int Deque::operator[](int index) const
{
	return array[index];
}

int& Deque::operator[](int index)
{
	return array[index];
}

Deque Deque::operator+(Deque const& rhs) const
{
	Deque tmp(*this);
	tmp += rhs;
	return tmp;
}

Deque& Deque::operator+=(const Deque& rhs)
{
	std::for_each(rhs.begin(), rhs.end(), [&](auto x) { PushBack(x); });
	return *this;
}

Deque::Iterator Deque::begin() const { return Deque::Iterator(this, 0); }

Deque::Iterator Deque::end() const { return Deque::Iterator(this, el_count); }

std::ostream& operator<<(std::ostream& os, Deque& instance)
{
	for (auto x : instance) { os << x << ' '; }       
	return os;
}

std::istream& operator>>(std::istream& is, Deque& instance)
{
	int input;
	is >> input;
	instance.PushBack(input);
	return is;
}

Deque::Iterator::Iterator(const Deque* p_iterated_set, int p_index)
	: iterated_dec(p_iterated_set), index(p_index) {}

const int& Deque::Iterator::operator*() const
{
	return iterated_dec->operator[](index);      /////////////////////////////////////////////////////////////////////////////////
}

typename Deque::Iterator& Deque::Iterator::operator++()//WHAT IS TYPENAME?
{
	index++;
	return *this;
}

bool Deque::Iterator::operator!=(const Iterator& rhs) const
{
	return !(*this == rhs);
}

bool Deque::Iterator::operator==(const Iterator& rhs) const
{
	return (iterated_dec == rhs.iterated_dec && index == rhs.index);
}
