#pragma once

#include <vector>
#include <string>
#include "Global.h"

enum operationsName {
	n_plus = 0,
	n_mult,
	n_divide,
	n_sqrt
};

//operations
 /*
double none(double left, double right);
double plus(double left, double right);
double minus(double left, double right);
double mult(double left, double right);
double divide(double left, double right);
double sqrt(double left, double right);
*/

namespace operations {
	Var none(std::vector<Member*>);
	Var plus(std::vector<Member*>);
	Var minus(std::vector<Member*>);
	Var mult(std::vector<Member*>);
	Var pow(std::vector<Member*>);
	Var divide(std::vector<Member*>);
	Var sqrt(std::vector<Member*>);
	Var abs(std::vector<Member*>);
	Var sin(std::vector<Member*>);
	Var cos(std::vector<Member*>);
	Var tan(std::vector<Member*>);
	Var mod(std::vector<Member*>);
}
extern const int operationsCount;
class Member;
class Operation {
public:
	Operation(std::string NAME = " EMPTY_OPERATION ", Var(*FUNC)(std::vector<Member*>) = operations::none, int MAX_MEMBERS = std::numeric_limits<int>::max(), int MIN_MEMBERS = 0);
	std::string name;
	Var(*func)(std::vector<Member*>);
	int maxMembers, minMembers;
};

extern const std::vector<Operation>op;

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
	long double fitness();
	virtual Var perform();
	virtual void resize();
	int operation = 0;
	std::vector<Var> results;

	int mSize, size;
	double fitn;
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
