#pragma once
#include "Model.h"

//class Iterator {                                  // Iterator
//public:
//	virtual void first() = 0;
//	virtual void next() = 0;
//	virtual bool isDone() = 0;
//	virtual int currentItem() const = 0;
//protected:
//	Iterator() {};
//};


//class DequeIter : public Iterator
//{
//private:
//
//	Model * dec;
//	int index;
//
//public:
//
//	DequeIter(Model *d)
//	{
//		dec = d;
//	}
//
//	virtual int currentItem() const;
//	virtual void first();
//	virtual void next();
//	virtual bool isDone();
//};
//
//void  DequeIter::first()
//{
//	index = 0;
//}
//void DequeIter::next()
//{
//	index++;
//}
//bool DequeIter::isDone()
//{
//	return index == dec->el_count;
//}
//int DequeIter::currentItem() const
//{
//	return dec->array[index];
//}
//
//
