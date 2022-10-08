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
	double none(std::vector<Member*>);
	double plus(std::vector<Member*>);
	double mult(std::vector<Member*>);
	double pow(std::vector<Member*>);
	double divide(std::vector<Member*>);
	double sqrt(std::vector<Member*>);
	double abs(std::vector<Member*>);
	double sin(std::vector<Member*>);
	double cos(std::vector<Member*>);
	double tan(std::vector<Member*>);
	double mod(std::vector<Member*>);
	double max(std::vector<Member*>);
	double min(std::vector<Member*>);
	
	namespace names {
		std::string none(std::vector<std::string>);
		std::string plus(std::vector<std::string>);
		std::string mult(std::vector<std::string>);
		std::string pow(std::vector<std::string>);
		std::string divide(std::vector<std::string>);
		std::string sqrt(std::vector<std::string>);
		std::string abs(std::vector<std::string>);
		std::string sin(std::vector<std::string>);
		std::string cos(std::vector<std::string>);
		std::string tan(std::vector<std::string>);
		std::string mod(std::vector<std::string>);
		std::string max(std::vector<std::string>);
		std::string min(std::vector<std::string>);
	}
}
extern const int operationsCount;
class Member;
class Operation {
public:
	Operation(std::string NAME, double(*FUNC)(std::vector<Member*>), std::string(*GET_NAME)(std::vector<std::string>), int MAX_MEMBERS, int MIN_MEMBERS);
	std::string name;
	double(*func)(std::vector<Member*>);
	std::string(*getName)(std::vector<std::string>);
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
	virtual double perform();
	virtual std::string getName();
	virtual void resize();
	int operation = 0;
	std::vector<long double> results;

	int mSize, size;
	long double fitn;
	std::vector<Member*> members;
protected:
	Member();
};

class Constant : public Member {
public:
	Constant(int mNum);
	virtual double perform();
	virtual std::string getName();
	virtual void resize();
	int mType;
};

int membersCount(Member* p);
Member* duplicate(Member* m);
Member* getMember(Member* m, int num, Member*&parent);
void swapPreset(int preset);
