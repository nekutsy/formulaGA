#include <iostream>
#include <string>
#include <ctime>

#include "Equation.h"
#include "GA.h"
#include "Global.h"

void display(int num, double scale, int width = 237, int height = 60, int offsetX = 0, int offsetY = 0);
void displayInfo(bool detail = false);

int main() {
	srand(time(0));
	createPreset();
	for (int i = 0; i < parentsCount; i++) {
		parents[i] = randMember(1 + rand() % 5, 2);
		maxFitness = std::max(maxFitness, parents[i]->fitness());
		//std::cout << parents[i]->getName() + " = " << parents[i]->perform() << std::endl;
	}
	//std::cout << std::endl;

	bool isRun = true, showInfo;
	int stepCount = 0;
	long double preMax;
	while (true) {
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
		std::cout << "improve: " << maxFitness - preMax << std::endl;
		std::cout << "maxFitness: " << maxFitness << std::endl;
		Member* b = parents[0];
		for (int i = 0; i < parentsCount; i++)
			if (parents[i]->fitn > b->fitn)
				b = parents[i];
		std::cout << "best: " << b->getName() << " = y" << std::endl;

		std::cout << std::endl;
		std::cout << "continue(y/n): ";
		std::cin >> ch;
		if (ch != 'y') {
			displayInfo(true);
			std::cout << std::endl << "for continue enter -1" << std::endl;
			int num;
			double scale;
			bool isStopped = true;
			while (isStopped) {
				do {
					std::cout << "num: ";
					std::cin >> num;
				} while (num < -1 || num >= parentsCount);
				if (num == -1)
					break;
				std::cout << "scale: ";
				std::cin >> scale;
				std::cout << parents[num]->getName() << " = y" << std::endl;
				display(num, scale);
			}
			std::cout << std::endl;
		}
	}
	std::cout << "watafak???";
}

const double scaleX = 0.5;
const char emptyCh = ' ', ch = '#', weakCh = '.',
abscissaCh = '-', ordinateCh = '|';

void display(int num, double scale, int width, int height, int offsetX, int offsetY) {
	double* results = new double[width];
	std::cout << std::endl;
	offsetX *= scale;
	offsetY *= scale;
	scale = 1 / scale;
	Member* m = parents[num];
	//std::cout << m->getName() + " = y" << std::endl;

	double preX = (*presets[0])[constants.size()].value;
	for (int i = -width / 2; i < width / 2; i++) {
		double x = double(i + offsetX) * scale * scaleX;
		(*presets[0])[constants.size()].value = x;
		results[width / 2 + i] = m->perform();
	}
	for (int i = -height / 2; i < height / 2; i++) {
		double y = -double(i + offsetY) * scale;
		for (int j = -width / 2; j < width / 2; j++) {
			double x = double(j + offsetX) * scale * scaleX;
			if (round(results[width / 2 + j] / scale) == round(y / scale))
				std::cout << ch;
			else if (round(funcs[funcNumber](std::vector<Var>{Var(x, "")}) / scale) == round(y / scale))
				std::cout << weakCh;
			else if (i + offsetY == 0)
				std::cout << abscissaCh;
			else if (j + offsetX == 0)
				std::cout << ordinateCh;
			else
				std::cout << emptyCh;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	delete[] results;
	(*presets[0])[constants.size()].value = preX;

}

const int miniWidth = 20, miniHight = 10;
void displayInfo(bool detail) {
	std::cout << std::endl << "best: " << std::endl;
	swapPreset(0);
	for (int i = 0; i < parentsCount; i++) {
		std::cout << "num: " << i << std::endl;
		std::cout << parents[i]->getName() + " = y" << std::endl;
		std::cout << "fitness: " << parents[i]->fitn << std::endl;
		//std::cout << "size: " << parents[i]->size << std::endl;
		if (detail) {
			float scale = float(miniWidth) / std::abs(maxFuncPresetVar - minFuncPresetVar);
			int offset = (minFuncPresetVar + maxFuncPresetVar) / 2.f;
			display(i, scale, 16, 8, offset);
		}
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
			if (parents[i]->results[j] != expectedResults[j])
				m = false;
	}
	std::cout << std::endl;

	std::cout << "maxFitness:" << std::endl;
	std::cout << "num: " << numBest << std::endl;
	std::cout << best->getName() + " = y" << std::endl;
	std::cout << "(" << best->fitn << ")" << std::endl;;

}