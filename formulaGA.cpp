#include <iostream>
#include <string>
#include <ctime>

#include "Equation.h"
#include "GA.h"
#include "Global.h"

int main() {
	init(2);
	srand(time(0));
	char ch;
	bool isRun = true, showInfo;
	int stepCount = 0;
	float preMax;
	time_t t = 0;

	createPreset();
	createParents();
	while (true) {
		preMax = maxFitness;
		std::cout << "showInfo(y/n): ";
		std::cin >> ch;
		showInfo = ch == 'y';
		std::cout << "step count: ";
		std::cin >> stepCount;
		t = time(0);
		for (int i = 0; i < stepCount; i++, stepNum++) {
			if (showInfo) {
				std::cout << "step: " << i + 1 << "/" << stepCount << " (" << stepNum << ")" << std::endl;
				std::cout << "avgFitness: " << avgFitness << std::endl;
				std::cout << "maxFitness: " << maxFitness << std::endl;
			}
			regulator(showInfo);

			//createGeneration();
			multithreadedCreateGeneration();
			processGeneration();
			multithreadedSelection();
			//selection();
		}
		//std::cout << "time: " << time(0) - t << std::endl;
		std::cout << "improve: " << maxFitness - preMax << std::endl;
		Member* b = parents[0];
		for (int i = 0; i < parentsCount; i++)
			if (parents[i]->fitn > b->fitn) {
				b = parents[i];
			}
		std::cout << "best: " << std::endl;
		displayInfo(dynamic_cast<Expression*>(b), true);

		std::cout << std::endl;
		std::cout << "continue(y/n): ";
		std::cin >> ch;
		if (ch != 'y') {
			for (int i = 0; i < parentsCount; i++) {
				std::cout << "num: " << i << std::endl;
				displayInfo(dynamic_cast<Expression*>(parents[i]), false);
				std::cout << std::endl;
			}

			int numBest = 0;
			Member* best = parents[0];
			for (int i = 0; i < parentsCount; i++)
				if (parents[i]->fitn > best->fitn) {
					best = parents[i];
					numBest = i;
				}

			std::cout << "maxFitness:" << std::endl;
			std::cout << "num: " << numBest << std::endl;
			displayInfo(dynamic_cast<Expression*>(best), true);
			std::cout << std::endl;

			std::cout << std::endl << "for continue enter -1" << std::endl;
			int num;
			bool isStopped = true;
			while (isStopped) {
				do {
					std::cout << "num: ";
					std::cin >> num;
				} while (num < -1 || num >= parentsCount);
				if (num == -1)
					break;
				display(num, 237, 60);
			}
			std::cout << std::endl;
		}
	}
	std::cout << "wtf??? chzh??? OMG???";
}