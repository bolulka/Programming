#include "Model.h"
#include "Visitor.h"
#include "Iterator.h"
#include "stdafx.h"
#include <utility>
#include <ostream>
#include <istream>
#include <iostream>
#include <algorithm>

Model::Model() : array_size(0), el_count(0) { }

Model::Model(Model&& other) : array_size(0), el_count(0)
{
	std::swap(array, other.array);
	std::swap(array_size, other.array_size);
	std::swap(el_count, other.el_count);
}

Model::Model(const Model& other) : array_size(0), el_count(0)
{
	for (int i = 0; i < other.el_count; i++)
	{
		PushBack(other.array[i]);
	}
}

Model::~Model()
{
	delete[] array;
	array_size = 0;
	el_count = 0;
}

void Model::PushBack(const int& instance)
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

void Model::PushFront(const int& instance)
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

void Model::PopBack()
{
	el_count--;
}

void Model::PopFront()
{
	for (int i = 0; i < el_count; i++)
	{
		array[i] = array[i + 1];
	}
	el_count--;
}

void Model::Clear()
{
	el_count = 0;
	array_size = 0;
}

bool Model::IsEmpty()
{
	if (el_count == 0)
		return true;
	else return false;
}

int	Model::Size()
{
	return el_count;
}

int Model::Front()
{
	return array[0];
}

int Model::Back()
{
	return array[el_count - 1];
}

void Model::Swap(int first_pos, int second_pos)
{
	if (el_count == 1) return;
	if (first_pos > el_count || second_pos > el_count) return;
	int el1;
	int el2;
	el1 = array[first_pos];
	el2 = array[second_pos];

	array[first_pos] = el2;
	array[second_pos] = el1;

}

std::wstring Model::to_wstring(/*int position*/)
{
	std::wstring str;
	ToStringVisitor ch;
	DequeIter it(this);
	for (it.first(); !it.isDone(); it.next())
	{
		ch.visit(it.currentItem());
		str += ch.getStr()+L" ";
	}
	//str= std::to_wstring(ch.getStr());
	return str;

	/*ToCharVisitor ch;
	DequeIter it(this);
	if (position == 0)
	{
		ch.visit(it.currentItem());
	}
	else {
		for (it.first(); !it.isDone(); it.next())
			ch.visit(it.currentItem());
	}*/
	//return ch.getChar();
	/*std::wstring str;
	str = std::to_wstring(*ch.getChar());
	return str;*/
};

bool Model::operator==(const Model& rhs)
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

bool Model::operator!=(const Model& rhs)
{
	return !(*this == rhs);
}

Model& Model::operator=(const Model& rhs)
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

Model Model::operator+(Model const& rhs) const
{
	Model tmp(*this);
	tmp += rhs;
	return tmp;
}

Model& Model::operator+=(const Model& rhs)
{
	//std::for_each(rhs.begin(), rhs.end(), [&](auto x) { PushBack(x); });
	if (el_count < rhs.el_count)
	{
		for (int i = 0; i < el_count; i++)
		{
			array[i] = array[i] + rhs.array[i];
		}
		for (int i = el_count; i < rhs.el_count; i++)
		{
			PushBack(rhs.array[i]);
		}
	}
	if (el_count > rhs.el_count)
	{
		for (int i = 0; i < rhs.el_count; i++)
		{
			array[i] = array[i] + rhs.array[i];
		}
	}
	if (el_count == rhs.el_count)
	{
		for (int i = 0; i < el_count; i++)
		{
			array[i] += rhs.array[i];
		}
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, Model& instance)
{
	DequeIter it(&instance);

	for (it.first(); !it.isDone(); it.next())
		os << it.currentItem() << ' ';
	return os;
}

std::istream& operator>>(std::istream& is, Model& instance)
{
	int input;
	is >> input;
	instance.PushBack(input);
	return is;
}


int Model::sumElements(Model &D) {
	SumElementVisitor vis;
	DequeIter it(&D);
	for (it.first(); !it.isDone(); it.next()) {
		vis.visit(it.currentItem());
	}
	return vis.getSum();
}
