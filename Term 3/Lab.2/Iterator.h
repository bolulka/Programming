#pragma once
#include "Model.h"

class Iterator {
	
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual bool isDone() = 0;
	virtual int currentItem() const = 0;

protected:
	Iterator() {};
};


class ModelIter : public Iterator
{
private:
	Model * dec;
	int index;

public:
	ModelIter(Model *d)
	{
		dec = d;
	}

	virtual int currentItem() const;
	virtual void first();
	virtual void next();
	virtual bool isDone();
};

void  ModelIter::first()
{
	index = 0;
}
void ModelIter::next()
{
	index++;
}
bool ModelIter::isDone()
{
	return index == dec->el_count;
}
int ModelIter::currentItem() const
{
	return dec->array[index];
}

