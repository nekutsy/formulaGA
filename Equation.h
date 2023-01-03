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
	double none(std::vector<Member*>&, int);
	double sum(std::vector<Member*>&, int);
	double dif(std::vector<Member*>&, int);
	double mult(std::vector<Member*>&, int);
	double pow(std::vector<Member*>&, int);
	double div(std::vector<Member*>&, int);
	double sqrt(std::vector<Member*>&, int);
	double abs(std::vector<Member*>&, int);
	double sin(std::vector<Member*>&, int);
	double cos(std::vector<Member*>&, int);
	double tan(std::vector<Member*>&, int);
	double mod(std::vector<Member*>&, int);
	double max(std::vector<Member*>&, int);
	double min(std::vector<Member*>&, int);
	
	namespace names {
		std::string none(std::vector<std::string>);
		std::string sum(std::vector<std::string>);
		std::string dif(std::vector<std::string>);
		std::string mult(std::vector<std::string>);
		std::string pow(std::vector<std::string>);
		std::string div(std::vector<std::string>);
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
	Operation(std::string NAME, double(*FUNC)(std::vector<Member*>&, int), std::string(*GET_NAME)(std::vector<std::string>), int MAX_MEMBERS, int MIN_MEMBERS);
	std::string name;
	double(*func)(std::vector<Member*>&, int);
	std::string(*getName)(std::vector<std::string>);
	int maxMembers, minMembers;
};

extern const std::vector<Operation>op;

class Member {
public:
	virtual double fitness() = 0;
	virtual void perform() = 0;
	virtual double perform(std::vector<double> vars) = 0;
	virtual std::string getName() = 0;
	virtual double getResult(int i) = 0;
	virtual Member* getMember(int i) = 0;
	virtual void resize() = 0;

	int mSize, size;
	int operation = 0;
	int nowPreset = 0;
	double fitn = std::numeric_limits<double>::lowest();
	virtual ~Member();
protected:
	Member(int OPERATION = 0);
};

class Const : public Member {
public:
	Const(int mNum);
	virtual double fitness();
	virtual void perform();
	virtual double perform(std::vector<double> vars);
	virtual std::string getName();
	virtual double getResult(int i);
	virtual Member* getMember(int i);
	virtual void resize();
	int mType;
};

class Var : public Member {
public:
	Var(int mNum);
	virtual double fitness();
	virtual void perform();
	virtual double perform(std::vector<double> vars);
	virtual std::string getName();
	virtual double getResult(int i);
	virtual Member* getMember(int i);
	virtual void resize();
	int mType;
private:
	double result;
};

class Expression : public Member {
public:
	Expression(std::vector<Member*> m, int OPERATION = 0);
	Expression(std::string s);
	virtual ~Expression();

	virtual double fitness();
	virtual void perform();
	virtual double perform(std::vector<double> vars);
	virtual std::string getName();
	virtual double getResult(int i);
	virtual Member* getMember(int i);
	virtual void resize();

	std::vector<Member*> members;
	std::vector<double> results;
};

int membersCount(Member* p);
Member* duplicate(Member* m);
Member* getAbsoluteMember(Member* m, int num, Member*& parent);
Member* randMember(int mSize, int maxDeep = 1, int opType = -1);
