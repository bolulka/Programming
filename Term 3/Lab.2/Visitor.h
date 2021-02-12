#pragma once
#include "Model.h"

class Visitor                                     // Visitor
{
public:
	virtual void visit(int) = 0;
};

class SumElementVisitor : public Visitor {

public:
	void visit(int item)
	{
		sum += item;
	}

	int getSum() const { return sum; }

private:
	int sum = 0;
};

class ToCharVisitor : public Visitor { //delete buf

private://c_str
	char* buf = new char[100];

public:

	void visit(int elem) {
		sprintf_s(buf, 100, "%d", elem);
	}

	char* getChar() const { return buf; }
};

