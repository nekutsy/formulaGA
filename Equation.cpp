#include "Equation.h"

#include <iostream>

#include "Global.h"

const std::vector<Operation>op = {
	Operation(" + ", operations::plus, operations::names::plus, std::numeric_limits<int>::max(), 1),
	Operation(" * ", operations::mult, operations::names::mult, std::numeric_limits<int>::max(), 1),
	Operation(" / ", operations::divide, operations::names::divide, 2, 2),
	//Operation(" ^ ", operations::pow, operations::names::pow, 2, 2),
	Operation(" sqrt ", operations::sqrt, operations::names::sqrt, 1, 1),
	Operation(" sin ", operations::sin, operations::names::sin, 1, 1),
	Operation(" cos ", operations::cos, operations::names::cos, 1, 1),
	Operation(" tan ", operations::tan, operations::names::tan, 1, 1),
	Operation(" abs ", operations::abs, operations::names::abs, 1, 1),
	Operation(" mod ", operations::mod, operations::names::mod, 2, 2),
	Operation(" max ", operations::max, operations::names::max, std::numeric_limits<int>::max(), 2),
	Operation(" min ", operations::min, operations::names::min, std::numeric_limits<int>::max(), 2),
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
	sizeW += -pow(size - expectedSize, 2) * sizeInfluence;
	int preset = nowPreset;

	for (int i = 0; i < presetsCount; i++) {
		long double out = expectedResults[nowPreset] - results[i];
		swapPreset(i);
		if (results[i] != results[i])
			if (expectedResults[i] == expectedResults[i])
				nanW += 1;
		else
			if (expectedResults[i] == expectedResults[i])
				outW += -pow(out, 2) * outInfluence;

		if (i != 0 && out == out && preOut == preOut)
			unevenW -= std::pow(preOut - (out), 2) * unevenInfluence;
		preOut = out;
	}
	swapPreset(preset);
	fitn = sizeW + (outW + unevenW) / presetsCount + nanW / presetsCount * nanPenalty;
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

double Member::perform() {
	int preset = nowPreset;
	for (int i = 0; i < mSize; i++)
		members[i]->perform();

	for (int j = 0; j < presetsCount; j++) {
		swapPreset(j);
		double out = op[operation].func(members);
		results[j] = out;
	}
	swapPreset(preset);
	return results[nowPreset];
}

std::string Member::getName() {
	std::string out;
	std::vector<std::string> names;
	names.resize(mSize);
	for (int i = 0; i < mSize; i++)
		names[i] = members[i]->getName();
	return op[operation].getName(names);
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

Member* getMember(Member* m, int num, Member*& parent) {
	if (num == 1 || m->operation == -1)
		return m;
	//std::cout << m << std::endl;
	int nowNum = 0;
	for (int i = 0; i < m->mSize; i++) {
		if (num < nowNum + m->members[i]->size) {
			return getMember(m->members[i], num - nowNum, m);
		}
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
	out->fitn = m->fitn;
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
		results[i] = (*presets[i])[mType].value;
	Member::operation = -1;
	resize();
}

void Constant::resize() {
	size = 1;
	mSize = 1;
}

double Constant::perform() {
	for (int i = 0; i < presetsCount; i++)
		results[i] = (*presets[i])[mType].value;
	return results[nowPreset];
}

std::string Constant::getName() {
	return g_members[0][mType].name;
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

double operations::none(std::vector<Member*> v) { return double(); }
double operations::plus(std::vector<Member*> in) {
	double out(in[0]->results[nowPreset]);
	for (int i = 1; i < in.size(); i++)
		out += in[i]->results[nowPreset];
	return out;
}
double operations::mult(std::vector<Member*> in) {
	double out(in[0]->results[nowPreset]);
	for (int i = 1; i < in.size(); i++)
		out *= in[i]->results[nowPreset];
	return out;
}
double operations::pow(std::vector<Member*> in) {
	return std::pow(in[0]->results[nowPreset], in[1]->results[nowPreset]);
}
double operations::divide(std::vector<Member*> in) {
	return in[0]->results[nowPreset] / in[1]->results[nowPreset];
}
double operations::sqrt(std::vector<Member*> in) {
	return std::sqrt(in[0]->results[nowPreset]);
}
double operations::abs(std::vector<Member*> in) {
	return std::abs(in[0]->results[nowPreset]);
}
double operations::sin(std::vector<Member*> in) {
	return std::sin(in[0]->results[nowPreset]);
}
double operations::cos(std::vector<Member*> in) {
	return std::cos(in[0]->results[nowPreset]);
}
double operations::tan(std::vector<Member*> in) {
	return std::tan(in[0]->results[nowPreset]);
}
double operations::mod(std::vector<Member*> in) {
	return std::fmod(in[0]->results[nowPreset], in[1]->results[nowPreset]);
}
double operations::max(std::vector<Member*> in) {
	long double out = in[0]->results[nowPreset];
	for (int i = 1; i < in.size(); i++)
		out = std::max(out, in[i]->results[nowPreset]);
	return out;
}
double operations::min(std::vector<Member*> in) {
	long double out = in[0]->results[nowPreset];
	for (int i = 1; i < in.size(); i++)
		out = std::min(out, in[i]->results[nowPreset]);
	return out;
}

std::string operations::names::none(std::vector<std::string> v) { return "NONE"; }
std::string operations::names::plus(std::vector<std::string> in) {
	std::string out = "(" + in[0];
	for (int i = 1; i < in.size(); i++)
		out += " + " + in[i];
	return out + ")";
}
std::string operations::names::mult(std::vector<std::string> in) {
	std::string out = "(" + in[0];
	for (int i = 1; i < in.size(); i++)
		out += " * " + in[i];
	return out + ")";
}
std::string operations::names::pow(std::vector<std::string> in) {
	return "(" + in[0] + ")^(" + in[1] + ")";
}
std::string operations::names::divide(std::vector<std::string> in) {
	return "(" + in[0] + " / " + in[1] + ")";
}
std::string operations::names::sqrt(std::vector<std::string> in) {
	return "sqrt(" + in[0] + ")";
}
std::string operations::names::abs(std::vector<std::string> in) {
	return "abs(" + in[0] + ")";
}
std::string operations::names::sin(std::vector<std::string> in) {
	return "sin(" + in[0] + ")";
}
std::string operations::names::cos(std::vector<std::string> in) {
	return "cos(" + in[0] + ")";
}
std::string operations::names::tan(std::vector<std::string> in) {
	return "tan(" + in[0] + ")";
}
std::string operations::names::mod(std::vector<std::string> in) {
	return "mod(" + in[0] + ", " + in[1] + ")";
}
std::string operations::names::max(std::vector<std::string> in) {
	std::string out = "max(" + in[0];
	for (int i = 1; i < in.size(); i++)
		out += ", " + in[i];
	return out + ")";
}
std::string operations::names::min(std::vector<std::string> in) {
	std::string out = "min(" + in[0];
	for (int i = 1; i < in.size(); i++)
		out += ", " + in[i];
	return out + ")";
}

Operation::Operation(std::string NAME = "_EMPTRY_OPERATION_", double(*FUNC)(std::vector<Member*>) = operations::none, std::string(*GET_NAME)(std::vector<std::string>) = operations::names::none, int MAX_MEMBERS = std::numeric_limits<int>::max(), int MIN_MEMBERS = 0) : name(NAME), func(FUNC), getName(GET_NAME), maxMembers(MAX_MEMBERS), minMembers(MIN_MEMBERS) {}

void swapPreset(int preset) {
	nowPreset = preset;
	g_members = presets[preset];
}
