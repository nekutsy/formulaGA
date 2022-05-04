#include <iostream>
#include "Equation.h"
#include "GA.h"

int main() {
	parents.resize(parentsCount);
	generation.resize(generationSize);
	result.resize(generationSize);
	rating.resize(generationSize);

	std::cout << "parents: " << std::endl;
	for (int i = 0; i < parentsCount; i++) {
		parents[i] = new Member(std::vector<Member*> {new Constant(members[0]), new Constant(members[0])}, n_plus);
		std::cout << parents[i]->members.size() << std::endl;
		std::cout << parents[i]->perform().name << " = " << parents[i]->perform().value << std::endl;
	}
	createGeneration();
	
	std::cout << std::endl << "generation: " << std::endl;
	for (int i = 0; i < generationSize; i++) {
		std::cout << generation[i]->perform().name << " = " << generation[i]->perform().value << std::endl;
	}
}