#include "UseFunctions.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

void f_createPreset() {
	int constSize = constants.size();
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

void f_regulator(bool detail) {
	mutationCount = std::max(r_baseMutation + sin(stepNum * M_PI / r_period) * r_mutationInfluence, 1.0);
	sizeMultiplier *= 0.999 + std::min(float(stepNum), 1000.f) / 1000000.f;
	if (detail) {
		std::cout << "mutationCount: " << mutationCount << std::endl;
		std::cout << "sizeMultiplier: " << sizeMultiplier << std::endl;
		std::cout << std::endl;
	}
}

const float scaleX = 0.5;
const char emptyCh = ' ', ch = '*', weakCh = '.', abscissaCh = '-', ordinateCh = '|';
void f_draw(Expression* e, float scale, int width, int height, int offsetX, int offsetY) {
	float* results = new float[width];
	offsetX *= scale;
	offsetY *= scale;
	scale = 1 / scale;

	std::vector<float> vars;
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

float minVar = 0;
float maxVar = 75;
int funcNumber = 5;
Member* targetFunc;

std::vector<float(*)(std::vector<float>)> funcs = {
   [](std::vector<float> v) { // 0
	   return targetFunc->perform(v);
   },
   [](std::vector<float> v) { // 1
	   return v[0] * v[0] + sqrt(abs(cos(float(fmod(v[0], 4)))));
   },
   [](std::vector<float> v) { // 2
	   return 2 / v[0] + v[0] * v[0] / 5 + v[0] / 3 - 5;
   },
   [](std::vector<float> v) { // 3
	   return float(rand() % 100 - 50);
   },
   [](std::vector<float> v) { // 4
	   return std::max(sin(v[0]), cos(v[0])) * std::max(tan(v[0]), atan(v[0]));
   },
   [](std::vector<float> v) { // 5
	   return pow(1.075f, v[0] + sin(v[0]) * 5);
   },
   [](std::vector<float> v) { // 6
	   float x = v[0], a = v[1], b = v[2], c = v[3];
	   return a * x * x + b * x + c;
   },
   [](std::vector<float> v) { // 7
	   float x = v[0];
	   return 0.1f * x * x + 0.5f * x + 2;
   },
   [](std::vector<float> v) { // 8
	   float v0 = v[0], t = v[1], a = v[2];
	   return v0 * t + a * t * t / 2;
   },
   [](std::vector<float> v) { // 9
	   float x = v[0];
	   return fmod(10 * x, x * x);
   },
   [](std::vector<float> v) { // 10
	   int n = std::max(int(v[0]), 0);

	   int* a = new int[std::max(n + 1, 3)];
	   a[0] = 1;
	   a[1] = 1;
	   for (int i = 2; i < n + 1; i++)
		   a[i] = a[i - 1] + a[i - 2];
	   float out = a[n];
	   delete[] a;
	   return out;
   },
   [](std::vector<float> v) { // 11
	   int n = std::max(int(v[0]), 0);
	   int out = 2;
	   int x = 0;
	   while (x < n) {
		   out += 1;
		   x += 1;
		   for (int i = 2; i < out; i++) {
			   if (out % i == 0) {
				   x -= 1;
				   break;
			   }
		   }
	   }
	   return float(out);
   },
   [](std::vector<float> v) { // 12
	   float x = v[0], a = v[1], b = v[2], c = v[3];
	   return a + b / (x + c);
   },
   [](std::vector<float> v) { // 13
	   float x = v[0], a = v[1], b = v[2];
	   return a * x + b;
   },
   [](std::vector<float> v) { // 14
	   float x = v[0];
	   return 2 * sin(x);
   },
};
