#include <iostream>
#include <string>
#include <ctime>

#include "Equation.h"
#include "GA.h"
#include "Global.h"

int main() {
	srand(time(0));
	createPreset();
	for (int i = 0; i < parentsCount; i++) {
		parents[i] = randMember(1 + rand() % 5);
		std::cout << parents[i]->perform().name + " = " << parents[i]->perform().value << std::endl;
	}
	std::cout << std::endl;

	bool isRun = true, showInfo;
	int stepCount = 0;
	long double preMax;
	while (isRun) {
		char ch;
		preMax = maxFitness;
		std::cout << "showInfo(y/n): ";
		std::cin >> ch;
		showInfo = ch == 'y';
		std::cout << "step count: ";
		std::cin >> stepCount;
		for (int i = 0; i < stepCount; i++) {
			if (showInfo) {
				std::cout << "step: " << i << std::endl;
				std::cout << "avgFitness: " << avgFitness << std::endl;
				std::cout << "maxFitness: " << maxFitness << std::endl;
				std::cout << std::endl;
			}
			createGeneration();
			performGeneration();
			selection();
		}
		std::cout << "improve = " << maxFitness - preMax << std::endl;
		std::cout << "maxFitness = " << maxFitness << std::endl;
		std::cout << std::endl;
		std::cout << "continue(y/n): ";
		std::cin >> ch;
		isRun = ch == 'y';
	}
	std::cout << std::endl << "best: " << std::endl;
	swapPreset(0);
	for (int i = 0; i < parentsCount; i++) {
		std::cout << "num: " << i << std::endl;
		std::cout << parents[i]->results[0].name + " = " << parents[i]->results[0].value << std::endl;
		std::cout << "fitness: " << parents[i]->fitn << std::endl;
		std::cout << "size: " << parents[i]->size << std::endl;
		std::cout << std::endl;
	}

	std::cout << std::endl << "matched: " << std::endl;
	int numBest = 0;
	Member* best = parents[0];
	for (int i = 0; i < parentsCount; i++) {
		if (parents[i]->fitn > best->fitn) {
			best = parents[i];
			numBest = i;
		}
		bool m = true;
		for (int j = 0; j < presetsCount; j++)
			if (parents[i]->results[j].value != expectedResults[j])
				m = false;
		if (m)
			std::cout << parents[i]->results[0].name + " = " << parents[i]->results[0].value << std::endl << std::endl;
	}
	std::cout << std::endl;

	std::cout << "maxFitness:" << std::endl;
	std::cout << best->results[0].name + " = " << best->results[0].value << std::endl;
	std::cout << "(" << best->fitn << ")" << std::endl;;
	std::cout << "num: " << numBest << std::endl;

	const int width = 237;
	const int height = 67;
	double *results = new double[width];
	const double scaleX = 0.5;
	const char emptyCh = ' ', ch = '#', weakCh = '.',
		abscissaCh = '-', ordinateCh = '|';
	swapPreset(0);
	while (true) {
		int num = 0;
		double scale = 0;
		std::cout << std::endl;
		std::cout << "num: ";
		std::cin >> num;
		std::cout << "scale: ";
		std::cin >> scale;
		scale = 1 / scale;
		Member* m = parents[num];
		std::cout << m->results[0].name + " = y" << std::endl;

		for (int i = -width / 2; i < width / 2; i++) {
			double x = double(i) * scale * scaleX;
			(*presets[0])[constants.size()].value = x;
			results[width / 2 + i] = m->perform().value;
		}
		for (int i = -height / 2; i < height / 2; i++) {
			double y = -double(i) * scale;
			for (int j = -width / 2; j < width / 2; j++) {
				double x = double(j) * scale * scaleX;
				if (round(results[width / 2 + j] / scale) == round(y / scale))
					std::cout << ch;
				else if (round(funcs[funcNumber](std::vector<Var>{Var(x, "")}) / scale) == round(y / scale))
					std::cout << weakCh;
				else if (i == 0)
					std::cout << abscissaCh;
				else if (j == 0)
					std::cout << ordinateCh;
				else
					std::cout << emptyCh;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "watafak???";
}