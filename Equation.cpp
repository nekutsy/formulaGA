#include "Equation.h"

#include <iostream>

#include "Global.h"

const std::vector<Operation>op = {
	Operation(" + ", operations::plus),
	Operation(" * ", operations::mult),
	Operation(" / ", operations::divide, 2, 2),
	Operation(" ^ ", operations::pow, 2, 2),
	Operation(" sqrt ", operations::sqrt, 1, 1),
	Operation(" sin ", operations::sin, 1, 1),
	Operation(" cos ", operations::cos, 1, 1),
	Operation(" tan ", operations::tan, 1, 1),
	Operation(" abs ", operations::abs, 1, 1),
	Operation(" mod ", operations::mod, 2, 2),
};
const int operationsCount = op.size();

Var::Var(double VALUE, std::string NAME) : value(VALUE), name(NAME) {}

void Member::resize() {
	for (int i = 0; i < members.size(); i++)
		members[i]->resize();
	mSize = members.size();
	size = membersCount(this);
}

Member::Member(std::vector<Member*> m, int OPERATION) : members(m), operation(OPERATION) {
	results.resize(presetsCount);
	resize();
	//perform();
}

Member::~Member() {
	for (int i = 0; i < members.size(); i++) {
		members[i]->~Member();
		delete members[i];
	}
}

long double Member::fitness() {
	long double sizeW = 0, outW = 0, nanW = 0, unevenW = 0, preOut = 0;
	int preset = nowPreset;
	for (int i = 0; i < presetsCount; i++) {
		long double _outW = 0, _nanW = 0;
		swapPreset(i);
		sizeW += -pow(size - expectedSize, 2) * sizeInfluence;
		if (results[i].value * 0 != 0)
			_nanW += nanPenalty;
		else
			_outW += -pow(expectedResults[nowPreset] - results[i].value, 2) * outInfluence;

		outW += _outW;
		nanW += _nanW;
		if (i != 0)
			unevenW -= std::pow(preOut - (_outW + nanW), 2) * unevenInfluence;
		preOut = _outW + _nanW;
	}
	swapPreset(preset);
	fitn = (sizeW + outW + nanW + unevenW) / presetsCount;
	return fitn;
}

/*
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
}*/

Var Member::perform() {
	int preset = nowPreset;
	for (int i = 0; i < mSize; i++)
		members[i]->perform();

	for (int j = 0; j < presetsCount; j++) {
		swapPreset(j);
		Var out = op[operation].func(members);
		results[j] = out;
	}
	swapPreset(preset);
	return results[nowPreset];
}

Member::Member() { results.resize(presetsCount); }

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
	Member* out = new Member(outMembers, m->operation);
	return out;
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
		results[i] = (*presets[i])[mType];

	Member::operation = -1;
	resize();
}

void Constant::resize() {
	size = 1;
	mSize = 1;
}

Var Constant::perform() {
	for (int i = 0; i < presetsCount; i++)
		results[i] = (*presets[i])[mType];
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
//double divide(double left, double right) { return left / right; }
double sqrt(double left, double right) { return pow(left, 1 / right); }

Var operations::none(std::vector<Member*> v) { return Var(); }
Var operations::plus(std::vector<Member*> in) {
	Var out(in[0]->results[nowPreset]);
	out.name = "(" + out.name;
	for (int i = 1; i < in.size(); i++) {
		out.name += " + " + in[i]->results[nowPreset].name;
		out.value += in[i]->results[nowPreset].value;
	}
	out.name += ")";
	return out;
}
Var operations::minus(std::vector<Member*> in) {
	Var out(in[0]->results[nowPreset]);
	out.name = "(" + out.name;
	for (int i = 1; i < in.size(); i++) {
		out.name += " - " + in[i]->results[nowPreset].name;
		out.value -= in[i]->results[nowPreset].value;
	}
	out.name += ")";
	return out;
}
Var operations::mult(std::vector<Member*> in) {
	Var out(in[0]->results[nowPreset]);
	out.name = "(" + out.name;
	for (int i = 1; i < in.size(); i++) {
		out.name += " * " + in[i]->results[nowPreset].name;
		out.value *= in[i]->results[nowPreset].value;
	}
	out.name += ")";
	return out;
}
Var operations::pow(std::vector<Member*> in) {
	return Var(std::pow(in[0]->results[nowPreset].value, in[1]->results[nowPreset].value), "(" + in[0]->results[nowPreset].name + ")^(" + in[1]->results[nowPreset].name + ")");
}
Var operations::divide(std::vector<Member*> in) {
	return Var(in[0]->results[nowPreset].value / in[1]->results[nowPreset].value, "(" + in[0]->results[nowPreset].name + " / " + in[1]->results[nowPreset].name + ")");
}
Var operations::sqrt(std::vector<Member*> in) {
	return Var(std::sqrt(in[0]->results[nowPreset].value), "sqrt(" + in[0]->results[nowPreset].name + ")");
}
Var operations::abs(std::vector<Member*> in) {
	return Var(std::abs(in[0]->results[nowPreset].value), "abs(" + in[0]->results[nowPreset].name + ")");
}
Var operations::sin(std::vector<Member*> in) {
	return Var(std::sin(in[0]->results[nowPreset].value), "sin(" + in[0]->results[nowPreset].name + ")");
}
Var operations::cos(std::vector<Member*> in) {
	return Var(std::cos(in[0]->results[nowPreset].value), "cos(" + in[0]->results[nowPreset].name + ")");
}
Var operations::tan(std::vector<Member*> in) {
	return Var(std::tan(in[0]->results[nowPreset].value), "tan(" + in[0]->results[nowPreset].name + ")");
}
Var operations::mod(std::vector<Member*> in) {
	return Var(std::fmod(in[0]->results[nowPreset].value, in[1]->results[nowPreset].value), "mod(" + in[0]->results[nowPreset].name + ", " + in[1]->results[nowPreset].name + ")");
}
Operation::Operation(std::string NAME, Var(*FUNC)(std::vector<Member*>), int MAX_MEMBERS, int MIN_MEMBERS) : name(NAME), func(FUNC), maxMembers(MAX_MEMBERS), minMembers(MIN_MEMBERS) {}

void swapPreset(int preset) {
	nowPreset = preset;
	members = presets[preset];
}
