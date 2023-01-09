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
float none(float left, float right);
float plus(float left, float right);
float minus(float left, float right);
float mult(float left, float right);
float divide(float left, float right);
float sqrt(float left, float right);
*/

namespace operations {
	float none(std::vector<Member*>&, int);
	float sum(std::vector<Member*>&, int);
	float dif(std::vector<Member*>&, int);
	float mult(std::vector<Member*>&, int);
	float pow(std::vector<Member*>&, int);
	float div(std::vector<Member*>&, int);
	float sqrt(std::vector<Member*>&, int);
	float abs(std::vector<Member*>&, int);
	float sin(std::vector<Member*>&, int);
	float cos(std::vector<Member*>&, int);
	float tan(std::vector<Member*>&, int);
	float mod(std::vector<Member*>&, int);
	float max(std::vector<Member*>&, int);
	float min(std::vector<Member*>&, int);
	
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
	Operation(std::string NAME, float(*FUNC)(std::vector<Member*>&, int), std::string(*GET_NAME)(std::vector<std::string>), int MAX_MEMBERS, int MIN_MEMBERS);
	std::string name;
	float(*func)(std::vector<Member*>&, int);
	std::string(*getName)(std::vector<std::string>);
	int maxMembers, minMembers;
};

extern const std::vector<Operation>op;

class Member {
public:
	virtual float fitness() = 0;
	virtual void perform() = 0;
	virtual float perform(std::vector<float> vars) = 0;
	virtual std::string getName() = 0;
	virtual float getResult(int i) = 0;
	virtual Member* getMember(int i) = 0;
	virtual void resize() = 0;
	virtual bool operator==(Member& right) = 0;

	int mSize, size;
	int operation = 0;
	int nowPreset = 0;
	float fitn = std::numeric_limits<float>::lowest();
	virtual ~Member();
protected:
	Member(int OPERATION = 0);
};

class Const : public Member {
public:
	Const(int mNum);
	virtual float fitness();
	virtual void perform();
	virtual float perform(std::vector<float> vars);
	virtual std::string getName();
	virtual float getResult(int i);
	virtual Member* getMember(int i);
	virtual void resize();
	virtual bool operator==(Member& right);
	int mType;
};

class Var : public Member {
public:
	Var(int mNum);
	virtual float fitness();
	virtual void perform();
	virtual float perform(std::vector<float> vars);
	virtual std::string getName();
	virtual float getResult(int i);
	virtual Member* getMember(int i);
	virtual void resize();
	virtual bool operator==(Member& right);
	int mType;
private:
	float result;
};

class Expression : public Member {
public:
	Expression(std::vector<Member*> m, int OPERATION = 0);
	Expression(std::string s);
	virtual ~Expression();

	virtual float fitness();
	virtual void perform();
	virtual float perform(std::vector<float> vars);
	virtual std::string getName();
	virtual float getResult(int i);
	virtual Member* getMember(int i);
	virtual void resize();
	virtual bool operator==(Member& right);

	std::vector<Member*> members;
	std::vector<float> results;
};

int membersCount(Member* p);
Member* duplicate(Member* m);
Member* getAbsoluteMember(Member* m, int num, Member*& parent);
Member* randMember(int mSize, int maxDeep = 1, int opType = -1);
