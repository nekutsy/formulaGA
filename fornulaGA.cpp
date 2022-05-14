#include <iostream>
#include <ctime>

#include "Equation.h"
#include "GA.h"
#include "Global.h"

int main() {
	srand(time(0));

	for (int i = 0; i < parentsCount; i++) {
		std::cout << 111;
		parents[i] = new Member(std::vector<Member*> {new Constant(0), new Constant(0)}, n_plus);
			//std::cout << parents[i]->perform().name << " = " << parents[i]->perform().value << std::endl;
	}

	for (int i = 0; i < 1500; i++) {
		std::cout << "step: " << i << std::endl;
		createGeneration();
		performGeneration();
		selection();
		std::cout << std::endl;
	}
	std::cout << std::endl << "generation: " << std::endl;
	swapPreset(0);
	for (int i = 0; i < parentsCount; i++) {
		std::cout << parents[i]->perform().name << " = " << parents[i]->perform().value << std::endl << std::endl;
	}
}