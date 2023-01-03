#include "UseFunctions.h"

#include <cmath>
#include <iostream>

void f_createPreset() {
	int constSize = constants.size();
	if (generateFuncPreset) {
		varValues.resize(presetsCountPerVar);
		for (int i = 0; i < presetsCountPerVar; i++)
			varValues[i] = minVar + (maxVar - minVar) / presetsCountPerVar * i;

		presetsCount = std::pow(presetsCountPerVar, varCount);
		presets.resize(presetsCount);
		expectedResults.resize(presetsCount);

		for (int i = 0; i < presetsCount; i++) {
			presets[i].resize(varCount);
			for (int j = 0; j < varCount; j++)
				presets[i][j] = varValues[(i / int(std::pow(presetsCountPerVar, j))) % presetsCountPerVar];
		}
	}
	else {
		presets.resize(presetsCount);
		for (int i = 0; i < presetsCount; i++) {
			int constSize = constants.size(), varSize = variables.size();
			presets[i].resize(constSize + varSize);
			for (int j = 0; j < constSize; j++)
				presets[i][j] = constants[j];
			for (int j = constSize; j < varSize; j++)
				presets[i][j] = variables[i][j - constSize];
		}
	}

	for (int i = 0; i < presetsCount; i++)
		expectedResults[i] = funcs[funcNumber](presets[i]);
}
void f_createParents() {
	for (int i = 0; i < parentsCount; i++)
		parents[i] = randMember(1 + rand() % 5, 2, 0);
}
void f_processGeneration() {
	multithreadedPerform();
}

const double scaleX = 0.5;
const char emptyCh = ' ', ch = '*', weakCh = '.', abscissaCh = '-', ordinateCh = '|';
void f_draw(Expression* e, float scale, int width, int height, int offsetX, int offsetY) {
	float* results = new float[width];
	offsetX *= scale;
	offsetY *= scale;
	scale = 1 / scale;

	std::vector<double> vars;
	vars.resize(varCount);
	for (int i = 0; i < varCount; i++)
		vars[i] = 1;

	for (int i = -width / 2; i < width / 2; i++) {
		float x = float(i + offsetX) * scale * scaleX;
		vars[0] = x;
		results[width / 2 + i] = e->perform(vars);
	}
	std::cout << std::endl;
	for (int i = -height / 2; i < height / 2; i++) {
		float y = -float(i + offsetY) * scale;
		for (int j = -width / 2; j < width / 2; j++) {
			float x = float(j + offsetX) * scale * scaleX;
			vars[0] = x;
			if (round(results[width / 2 + j] / scale) == round(y / scale))
				std::cout << ch;
			else if (round(funcs[funcNumber](vars) / scale) == round(y / scale))
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
}
void f_display(int num, int width, int height) {
	float scale;
	std::cout << "scale: ";
	std::cin >> scale;
	std::cout << parents[num]->getName() << std::endl;
	f_draw(dynamic_cast<Expression*>(parents[num]), scale, 237, 60, 0, 0);
}

const int miniWidth = 20, miniHight = 10;
void f_displayInfo(Expression* e, bool detail) {
	std::cout << e->getName() + " = y" << std::endl;
	if (detail) {
		std::cout << "fitness: " << e->fitn << std::endl;
		std::cout << "size: " << e->size << std::endl;
		float scale = float(miniWidth) / std::abs(maxVar - minVar);
		int offset = (minVar + maxVar) / 2.f;
		f_draw(e, scale, 16, 8, offset);
	}
}