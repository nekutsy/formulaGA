#include "Equation.h"

#include <iostream>
#include <string_view>

#include "Global.h"

const std::vector<Operation>op = {
	Operation("sum", operations::sum, operations::names::sum, std::numeric_limits<int>::max(), 2),
	//Operation("dif", operations::dif, operations::names::dif, std::numeric_limits<int>::max(), 2),
	Operation("mult", operations::mult, operations::names::mult, std::numeric_limits<int>::max(), 2),
	Operation("div", operations::div, operations::names::div, 2, 2),
	//Operation("pow", operations::pow, operations::names::pow, 2, 2),
	Operation("sqrt", operations::sqrt, operations::names::sqrt, 1, 1),
	//Operation("sin", operations::sin, operations::names::sin, 1, 1),
	//Operation("cos", operations::cos, operations::names::cos, 1, 1),
	//Operation("tan", operations::tan, operations::names::tan, 1, 1),
	Operation("abs", operations::abs, operations::names::abs, 1, 1),
	Operation("mod", operations::mod, operations::names::mod, 2, 2),
	Operation("max", operations::max, operations::names::max, std::numeric_limits<int>::max(), 2),
	Operation("min", operations::min, operations::names::min, std::numeric_limits<int>::max(), 2),
};
const int operationsCount = op.size();

Member::Member(int OPERATION) : operation(OPERATION) {}
Member::~Member() {}
double Expression::fitness() {
	double sizeW = 0, outW = 0, nanW = 0, unevenW = 0, preOut = 0;
	sizeW += -pow(size - expectedSize, 2) * sizeMultiplier;

	for (int i = 0; i < presetsCount; i++) {
		long double out = expectedResults[i] - getResult(i);
		if (getResult(i) * 0 != getResult(i) * 0) {
			if (expectedResults[i] * 0 == expectedResults[i] * 0)
				nanW += 1;
		}
		else
			if (out * 0 == out * 0) {
				double uw = pow(out, 2) * outMultiplier;
				//for (int j = 0; j < varCount && false; j++) outW -= uw * std::abs(presets[i][constants.size() + j] - presets[std::max(i - 1, 0)][constants.size() + j]);
				outW -= uw;
			}

		if (i != 0 && out * 0 == out * 0 && preOut * 0 == preOut * 0) {
			double uv = std::pow(preOut - out, 2) * unevenMultiplier;
			//for (int j = 0; j < varCount && false; j++) unevenW -= uv * std::abs(presets[i][constants.size() + j] - presets[i - 1][constants.size() + j]);
			unevenW -= uv;
		}
		preOut = out;
	}
	fitn = sizeW + (outW + unevenW) / presetsCount + nanW / presetsCount * nanPenalty;
	return fitn;
}

void Expression::resize() {
	for (int i = 0; i < members.size(); i++)
		members[i]->resize();
	mSize = members.size();
	size = membersCount(this);
}

Expression::Expression(std::vector<Member*> m, int OPERATION) : members(m), Member(OPERATION) {
	results.resize(presetsCount + 1);
	resize();
}

Expression::Expression(std::string in) {
	//std::string in(in.begin(), std::remove(in.begin(), in.end(), ' '));
	int nameSize = in.find('(');
	if (nameSize == size_t(-1)) {
		std::cout << "none operation";
		abort();
	}
	int opType = -1;
	for (int i = 0; i < op.size(); i++) {
		if (op[i].name.size() == nameSize) {
			bool b = true;
			for (int j = 0; j < nameSize && b; j++)
				b = op[i].name[j] == in[j];
			if (b) {
				opType = i;
				break;
			}
		}
	}
	if (opType == -1) {
		std::cout << "undefined operation " << std::string_view(in.c_str(), nameSize);
		abort();
	}
	int segmentBegin = 0, segmentEnd = nameSize, segmentSize = 0;
	while (segmentEnd < in.size() - 2) {
		segmentBegin = segmentEnd + 1;
		segmentEnd = segmentBegin;

		for (int bracketCount = 0; (bracketCount > 0 || in[segmentEnd] != ',') && segmentEnd < in.size() - 1; segmentEnd++)
			if (in[segmentEnd] == '(')
				bracketCount += 1;
			else if (in[segmentEnd] == ')')
				bracketCount -= 1;

		segmentSize = segmentEnd - segmentBegin;
		bool isConst = false;

		for (int j = 0; j < constants.size() + varNames.size(); j++) {
			std::string name;
			if (j < constants.size())
				name = constantNames[j];
			else
				name = varNames[j - constants.size()];

			if (name.size() == segmentSize) {
				bool b = true;
				for (int k = segmentBegin; k < segmentEnd && b; k++)
					b = name[k - segmentBegin] == in[k];
				if (b) {
					if (j < constants.size())
						members.push_back(new Const(j));
					else
						members.push_back(new Var(j - constants.size()));
					isConst = true;
					break;
				}
			}
		}
		if (!isConst) {
			members.push_back(new Expression(std::string(in.begin() + segmentBegin, in.begin() + segmentEnd)));
		}
	}
	results.resize(presetsCount + 1);
	resize();
	operation = opType;
}

Expression::~Expression() {
	for (int i = 0; i < members.size(); i++)
		delete members[i];
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
			out = operations[operation].func(out, members[i]->results[j]);
			out.name = out.name + operations[operation].name + "(" + members[i]->results[j].name + ")";
		}
		results[j] = out;
	}
	swapPreset(preset);
	return results[nowPreset];
}*/
void Expression::perform() {
	for (int i = 0; i < mSize; i++)
		members[i]->perform();
	for (int i = 0; i < presetsCount; i++)
		results[i] = op[operation].func(members, i);
}
double Expression::perform(std::vector<double> vars) {
	for (int i = 0; i < mSize; i++)
		members[i]->perform(vars);
	results[presetsCount] = op[operation].func(members, presetsCount);
	return results[presetsCount];
}
std::string Expression::getName() {
	std::string out;
	std::vector<std::string> names;
	names.resize(mSize);
	for (int i = 0; i < mSize; i++)
		names[i] = members[i]->getName();
	return op[operation].getName(names);
}
double Expression::getResult(int i) {
	return results[i];
}
Member* Expression::getMember(int i) {
	return members[i];
}
Const::Const(int M_TYPE) : Member(), mType(M_TYPE) {
	Member::operation = -1;
	resize();
}
void Const::resize() {
	size = 1;
	mSize = 1;
}

double Const::fitness() { return std::numeric_limits<double>::lowest(); }
void Const::perform() {}
double Const::perform(std::vector<double> vars) {
	return constants[mType];
}
std::string Const::getName() {
	return constantNames[mType];
}
double Const::getResult(int i) {
	return constants[mType];
}
Member* Const::getMember(int i) {
	return 0;
}

Var::Var(int M_TYPE) : Member(), mType(M_TYPE) {
	Member::operation = -2;
	resize();
}
void Var::resize() {
	size = 1;
	mSize = 1;
}
double Var::fitness() { return std::numeric_limits<double>::lowest(); }
void Var::perform() {}
double Var::perform(std::vector<double> vars) {
	result = vars[mType];
	return result;
}
std::string Var::getName() {
	return varNames[mType];
}
double Var::getResult(int i) {
	if (i == presetsCount)
		return result;
	return presets[i][mType];
}
Member* Var::getMember(int i) {
	return 0;
}

Member* getAbsoluteMember(Member* m, int num, Member*& parent) {
	if (num == 1 || m->operation < 0)
		return m;
	//std::cout << m << std::endl;
	int nowNum = 0;
	for (int i = 0; i < m->mSize; i++) {
		if (num < nowNum + m->getMember(i)->size) {
			return getAbsoluteMember(m->getMember(i), num - nowNum, m);
		}
		else
			nowNum += m->size;
	}
	return 0;
}

Member* duplicate(Member* m) {
	std::vector<Member*> outMembers;
	outMembers.resize(m->mSize);
	for (int i = 0; i < m->mSize; i++)
		if (m->getMember(i)->operation == -1)
			outMembers[i] = new Const((dynamic_cast<Const*>(m->getMember(i)))->mType);
		else if (m->getMember(i)->operation == -2)
			outMembers[i] = new Var((dynamic_cast<Var*>(m->getMember(i)))->mType);
		else
			outMembers[i] = duplicate(m->getMember(i));

	Member* out = new Expression(outMembers, m->operation);
	out->fitn = m->fitn;
	return out;
}

int membersCount(Member* p) {
	int out = 0;
	if (p->mSize > 1)
		for (int i = 0; i < p->mSize; i++)
			if (p->getMember(i)->mSize > 1)
				out += membersCount(p->getMember(i));
			else
				out++;
	else
		return 1;
	return out;
}

Member* randMember(int mSize, int maxDeep, int opType) {
	int operation = (opType < 0) ? (rand() % operationsCount) : opType,
		size = std::max(std::min(mSize, op[operation].maxMembers), op[operation].minMembers);
	std::vector<Member*> out;
	out.resize(size);
	for (int i = 0; i < size; i++)
		if (maxDeep > 1 && rand() % 2)
			out[i] = randMember(mSize, maxDeep - 1);
		else if (rand() % 2)
			out[i] = new Var(rand() % varCount);
		else
			out[i] = new Const(rand() % constants.size());

	return new Expression(out, operation);
}

double none(double left, double right) { return 0.0; }
double plus(double left, double right) { return left + right; }
double minus(double left, double right) { return left - right; }
double mult(double left, double right) { return left * right; }
//double divide(double left, double right) { return left / right; }
double sqrt(double left, double right) { return pow(left, 1 / right); }

double operations::none(std::vector<Member*>& in, int presetNum) { return std::numeric_limits<double>::quiet_NaN(); }
double operations::sum(std::vector<Member*>& in, int presetNum) {
	double out(in[0]->getResult(presetNum));
	for (int i = 1; i < in.size(); i++)
		out += in[i]->getResult(presetNum);
	return out;
}
double operations::dif(std::vector<Member*>& in, int presetNum) {
	double out(in[0]->getResult(presetNum));
	for (int i = 1; i < in.size(); i++)
		out -= in[i]->getResult(presetNum);
	return out;
}
double operations::mult(std::vector<Member*>& in, int presetNum) {
	double out(in[0]->getResult(presetNum));
	for (int i = 1; i < in.size(); i++)
		out *= in[i]->getResult(presetNum);
	return out;
}
double operations::pow(std::vector<Member*>&in, int presetNum) {
	return std::pow(in[0]->getResult(presetNum), in[1]->getResult(presetNum));
}
double operations::div(std::vector<Member*>&in, int presetNum) {
	return in[0]->getResult(presetNum) / in[1]->getResult(presetNum);
}
double operations::sqrt(std::vector<Member*>&in, int presetNum) {
	return std::sqrt(in[0]->getResult(presetNum));
}
double operations::abs(std::vector<Member*>&in, int presetNum) {
	return std::abs(in[0]->getResult(presetNum));
}
double operations::sin(std::vector<Member*>&in, int presetNum) {
	return std::sin(in[0]->getResult(presetNum));
}
double operations::cos(std::vector<Member*>&in, int presetNum) {
	return std::cos(in[0]->getResult(presetNum));
}
double operations::tan(std::vector<Member*>&in, int presetNum) {
	return std::tan(in[0]->getResult(presetNum));
}
double operations::mod(std::vector<Member*>&in, int presetNum) {
	return std::fmod(in[0]->getResult(presetNum), in[1]->getResult(presetNum));
}
double operations::max(std::vector<Member*>&in, int presetNum) {
	double out = in[0]->getResult(presetNum);
	for (int i = 1; i < in.size(); i++)
		out = std::max(out, in[i]->getResult(presetNum));
	return out;
}
double operations::min(std::vector<Member*>& in, int presetNum) {
	double out = in[0]->getResult(presetNum);
	for (int i = 1; i < in.size(); i++)
		out = std::min(out, in[i]->getResult(presetNum));
	return out;
}

std::string operations::names::none(std::vector<std::string> v) { return "NONE"; }
std::string operations::names::sum(std::vector<std::string> in) {
	std::string out = "(" + in[0];
	for (int i = 1; i < in.size(); i++)
		out += " + " + in[i];
	return out + ")";
}
std::string operations::names::dif(std::vector<std::string> in) {
	std::string out = "(" + in[0];
	for (int i = 1; i < in.size(); i++)
		out += " - " + in[i];
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
std::string operations::names::div(std::vector<std::string> in) {
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

Operation::Operation(std::string NAME = "_EMPTRY_OPERATION_", double(*FUNC)(std::vector<Member*>&, int) = operations::none, std::string(*GET_NAME)(std::vector<std::string>) = operations::names::none, int MAX_MEMBERS = std::numeric_limits<int>::max(), int MIN_MEMBERS = 0) : name(NAME), func(FUNC), getName(GET_NAME), maxMembers(MAX_MEMBERS), minMembers(MIN_MEMBERS) {}
