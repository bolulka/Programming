#pragma once
#include "Model.h"

class Visitor                                     // Visitor
{
public:
	virtual void visit(int) = 0;
};

class SumElementVisitor : public Visitor {
public:
	void visit(int item) {
		sum += item;
	}
	int getSum() const { return sum; }
private:
	int sum = 0;
};

class ToStringVisitor : public Visitor { 
private:
	//char* buf = new char[100];
	std::wstring str;
public:

	void visit(int elem) {
		//sprintf_s(buf, 100, "%d", elem);
		str = std::to_wstring(elem);
	}

	std::wstring getStr() const { return str; }
};


