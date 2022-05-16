#pragma once

#include <vector>
#include <string>
int const presetsCount = 15;
#include "Global.h"

enum operationsName {
	n_plus = 0,
	//n_minus,
	n_mult,
	//n_divide,
	n_sqrt
};

//operations
double none(double left, double right);
double plus(double left, double right);
double minus(double left, double right);
double mult(double left, double right);
double divide(double left, double right);
double sqrt(double left, double right);
const int operationsCount = 3;

class Operation {
public:
	Operation(std::string NAME = " EMPTY_OPERATION ", double(*FUNC)(double left, double right) = none);
	std::string name;
	double(*func)(double left, double right);
};

extern std::vector<Operation>operations;

class Var {
public:
	Var(double VALUE = 0, std::string NAME = "EMPTY");
	double value;
	std::string name;
};

class Member {
public:
	Member(std::vector<Member*> m, int OPERATION = 0);
	~Member();
	virtual Var perform();
	virtual void resize();
	int operation = 0;
	std::array<Var, presetsCount> results;

	int mSize;
	int size;
	std::vector<Member*> members;
protected:
	Member();
};

class Constant : public Member {
public:
	Constant(int mNum);
	virtual Var perform();
	virtual void resize();
	int mType;
};

int membersCount(Member* p);
Member* duplicate(Member* m);
Member* getMember(Member* m, int num);
void swapPreset(int preset);
