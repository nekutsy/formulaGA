#include "Equation.h"

#include <iostream>

std::vector<Operation>operations = {
	Operation(" + ", plus),
	Operation(" - ", minus),
	Operation(" * ", mult),
	Operation(" / ", divide),
	Operation(" ^ ", pow),
	Operation(" sqrt ", sqrt)
};

Var::Var(double VALUE, std::string NAME) : value(VALUE), name(NAME) {}

Member::Member(std::vector<Member*> m, int OPERATION) : members(m), size(m.size()), operation(OPERATION) {}

Member::~Member() {
	for (int i = 0; i < members.size(); i++) {
		members[i]->~Member();
		delete members[i];
	}
}

Var Member::perform() {
	Var out = members[0]->perform();
	for (int i = 1; i < size; i++) {
		out.value = operations[operation].func(out.value, members[i]->perform().value);
		out.name = out.name + operations[operation].name + members[i]->perform().name;
	}
	return out;
}

Member* getMember(Member* m, int num) {
	std::cout << "mptr: " << m << std::endl;
	if (num == 1 || m->operation == -1)
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
}

Member* duplicate(Member* m) {
	std::cout << "size2:" << m->size << std::endl;
	std::cout << "mptr: " << m << std::endl;
	std::vector<Member*> outMembers;
	outMembers.resize(m->members.size());
	std::cout << "size3:" << m->members.size() << std::endl;
	std::cout << "size4:" << outMembers.size() << std::endl;
	//std::cout << "mSize: " << outMembers.size() << std::endl;
	for (int i = 0; i < m->size; i++) {
		if (m->members[i]->operation != -1) {
			outMembers[i] = duplicate(m->members[i]);
			std::cout << "re" << std::endl;
		}
		else {
			outMembers[i] = new Constant(*dynamic_cast<Constant*>(m->members[i]));
		}
	}
	Member* out = new Member(outMembers, m->operation);
	return out;
} 

int membersCount(Member* p) {
	int out = 0;
	if (p->size > 1)
		for (int i = 0; i < p->size; i++)
			if (p->members[i]->size > 1)
				out += membersCount(p->members[i]);
			else
				out++;
	else
		return 1;
	return out;
}

Constant::Constant(Var VAR) : value(VAR), Member(std::vector<Member*>(), -1) {}

Var Constant::perform() {
	return value;
}

/*Member* out;
	if (m->size > 1) {
		std::vector<Member*> outMembers;
		for (int i = 0; i < m->size; i++)
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
