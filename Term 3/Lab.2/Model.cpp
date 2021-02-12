#include "Model.h"
#include "Visitor.h"
#include "Iterator.h"
#include <iostream>
#include <string>

using namespace std;

Model::Model() :el_count(0), array_size() {}

Model::Model(const Model& obj)
	:
	el_count(obj.el_count),
	array_size(obj.array_size)
{
	for (int i = 0; i < obj.el_count; i++)
	{
		PushBack(array[i]);
	}
}



Model::Model(Model&& obj)
	: 
	el_count(obj.el_count),
	array_size(obj.array_size)

{
	
	swap(array, obj.array);
	swap(array_size, obj.array_size);
	swap(el_count, obj.el_count);
}

Model::~Model()
{
	array_size = 0;
	el_count = 0;
}

void Model::PushFront(int data)
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
	array[0] = data;
	el_count++;
}


void Model::PushBack(int data)
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
		
	}
	array[el_count] = data;
	el_count++;
}

void Model::PopFront()

{
	if (IsEmpty()) return;
	for (int i = 0; i < el_count; i++)
	{
		array[i] = array[i + 1];
	}
	el_count--;
}

void Model::PopBack()
{
	if (IsEmpty()) return;
	el_count--;
}

int Model::Front()
{
	if (IsEmpty()) return 0;
	else 
	return array[0];
	
}

int Model::Back()
{
	if (IsEmpty()) return 0;
	else 
	return array[el_count - 1];
	
}

bool Model::IsEmpty()
{
	if (el_count == 0) return true;
	else return false;
}


void Model::Clear()
{
	if (IsEmpty()) return;
	else
	{
		el_count = 0;
		array_size = 0;
	}
}

void Model::SwapModel(Model& D2)
{
	if (IsEmpty()) return;
	else
	{
		swap(array, D2.array);
		swap(array_size, D2.array_size);
	}
}

int Model::GetSize()
{
	return el_count;
}

wstring Model::toString() {

	ToCharVisitor ch;
	ModelIter it(this);

	for (it.first(); !it.isDone(); it.next())
		ch.visit(it.currentItem());

	wstring str;
	str = to_wstring(*ch.getChar());

	return str;
}


int Model::sumElements(Model &D) {
	SumElementVisitor vis;
	ModelIter it(&D);
	for (it.first(); !it.isDone(); it.next()) {
		vis.visit(it.currentItem());
	}
	return vis.getSum();
}

ostream& operator << (ostream& out, Model& D) {

	ModelIter it(&D);

	for (it.first(); !it.isDone(); it.next())
		out << it.currentItem() << ' ';
	return out;
}

bool operator == (Model &l, Model &r)
{
	ModelIter itl(&l);
	ModelIter itr(&r);

	if (l.GetSize() != r.GetSize()) return false;
	for (itl.first(), itr.first(); !itl.isDone(); itl.next(), itr.next())
	{
		if (itl.currentItem() != itr.currentItem())
			return false;
	}
	return true;
}

bool operator != (Model &l, Model &r)
{
	ModelIter itl(&l);
	ModelIter itr(&r);

	if (l.GetSize() != r.GetSize()) return true;
	for (itl.first(), itr.first(); !itl.isDone(); itl.next(), itr.next())
	{
		if (itl.currentItem() != itr.currentItem())
			return true;
	}
	return false;
}

int operator ++(Model &D)
{
	ModelIter it(&D);
	return it.currentItem() + 1;
}
