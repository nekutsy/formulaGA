#include "Equation.h"

#include <iostream>

#include "Global.h"

std::vector<Operation>operations = {
	Operation(" + ", plus),
	//Operation(" - ", minus),
	Operation(" * ", mult),
	//Operation(" / ", divide),
	Operation(" ^ ", pow),
	//Operation(" sqrt ", sqrt)
};

Var::Var(double VALUE, std::string NAME) : value(VALUE), name(NAME) {}

void Member::resize() {
	for (int i = 0; i < members.size(); i++)
		members[i]->resize();
	mSize = members.size();
	size = membersCount(this);
}

Member::Member(std::vector<Member*> m, int OPERATION) : members(m), operation(OPERATION) {
	resize();
	perform();
}

Member::~Member() {
	for (int i = 0; i < members.size(); i++) {
		members[i]->~Member();
		delete members[i];
	}
}

Var Member::perform() {
	int preset = nowPreset;
	for (int i = 0; i < mSize; i++)
		members[i]->perform();

	for (int j = 0; j < presetsCount; j++) {
		swapPreset(j);
		Var out = members[0]->perform();
		for (int i = 1; i < mSize; i++) {
			out.value = operations[operation].func(out.value, members[i]->results[j].value);
			out.name = out.name + operations[operation].name + "(" + members[i]->results[j].name + ")";
		}
		results[j] = out;
	}
	swapPreset(preset);
	return results[nowPreset];
}

Member::Member() {}

//Member::Member() : size(-1) {}

/*
Member* getMember(Member* m, int num) {
	if (num == 1 || m->operation == -1 || m->mSize <= 1)
		return m;
	int i = 0, nowNum = 0;
	Member* out;
	while (true) {
		if (i == num) {
			out = m->members[i];
			break;
		}
		if (num < membersCount(m->members[i])) {
			nowNum += membersCount(m->members[i]);
			i++;
		}
		else {
			out = getMember(m->members[i], num - i);
			break;
		}
	}
	return out;
}*/

Member* getMember(Member* m, int num) {
	if (num == 1 || m->operation == -1)
		return m;
	//std::cout << m << std::endl;
	int nowNum = 0;
	for (int i = 0; i < m->mSize; i++) {
		if (num < nowNum + m->members[i]->size)
			return getMember(m->members[i], num - nowNum);
		else
			nowNum += m->size;
	}
	return 0;
}

Member* duplicate(Member* m) {
	std::vector<Member*> outMembers;
	outMembers.resize(m->mSize);
	for (int i = 0; i < m->mSize; i++) {
		if (m->members[i]->operation != -1 || m->members[i]->mSize > 1) {
			outMembers[i] = duplicate(m->members[i]);
		}
		else {
			outMembers[i] = new Constant((dynamic_cast<Constant*>(m->members[i]))->mType);
		}
	}
	return new Member(outMembers, m->operation);
} 

int membersCount(Member* p) {
	int out = 0;
	if (p->mSize > 1)
		for (int i = 0; i < p->mSize; i++)
			if (p->members[i]->mSize > 1)
				out += membersCount(p->members[i]); ///
			else
				out++;
	else
		return 1;
	return out;
}

Constant::Constant(int M_TYPE) : Member(), mType(M_TYPE) {
	for (int i = 0; i < presetsCount; i++)
		results[i] = presets[i][mType];

	Member::operation = -1;
	resize();
}

void Constant::resize() {
	size = 1;
	mSize = 1;
}

Var Constant::perform() {
	return results[nowPreset];
}

/*Member* out;
	if (m->mSize > 1) {
		std::vector<Member*> outMembers;
		for (int i = 0; i < m->mSize; i++)
			outMembers.push_back(duplicate(m->members[i]));
		*out = *m;
	}
	else {
		out = new Multiplier(m->perform());
	}*/

double none(double left, double right) { return 0.0; }
double plus(double left, double right) { return left + right; }
double minus(double left, double right) { return left - right; }
double mult(double left, double right) { return left * right; }
double divide(double left, double right) { return left / right; }
double sqrt(double left, double right) { return pow(left, 1 / right); }

Operation::Operation(std::string NAME, double(*FUNC)(double left, double right)) : name(NAME), func(FUNC) {}

void swapPreset(int preset) {
	nowPreset = preset;
	members = presets[preset];
}