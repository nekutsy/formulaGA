#include <iostream>
#include <ctime>

#include "Equation.h"
#include "GA.h"
#include "Global.h"

int main() {
	srand(time(0));

	for (int i = 0; i < parentsCount; i++) {
		parents[i] = new Member(std::vector<Member*> {new Constant(0), new Constant(0)}, 0);
			//std::cout << parents[i]->perform().name << " = " << parents[i]->perform().value << std::endl;
	}

	for (int i = 0; i < 1 && mScore > minScore; i++) {
		std::cout << "step: " << i << std::endl;
		std::cout << "mutationsCount: " << mutationCount << std::endl;
		std::cout << "mScore: " << mScore << std::endl;
		createGeneration();
		performGeneration();
		selection();
		std::cout << std::endl;
	}
	std::cout << std::endl << "best: " << std::endl;
	swapPreset(0);
	for (int i = 0; i < parentsCount; i++) {
		std::cout << parents[i]->results[0].name << " = " << parents[i]->results[0].value << std::endl << std::endl;
	}

	std::cout << std::endl << "matched: " << std::endl;
	for (int i = 0; i < parentsCount; i++) {
		bool m = true;
		for (int j = 0; j < presetsCount; j++)
			if (parents[i]->results[j].value != expectedResults[j])
				m = false;
		if (m)
			std::cout << parents[i]->results[0].name << " = " << parents[i]->results[0].value << std::endl << std::endl;
	}

	while (true)
		std::cin.get();
}