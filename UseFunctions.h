#pragma once

#include "Equation.h"
#include "Global.h"
#include "BaseGA.h"

void f_createPreset();
void f_createParents();
void f_processGeneration(); // ~perform + fitness

void f_draw(Expression* e, float scale, int width = 237, int height = 60, int offsetX = 0, int offsetY = 0);
void f_display(int num, int width = 237, int height = 60);
void f_displayInfo(Expression* e, bool detail = false);

const std::vector<double(*)(std::vector<double>)> funcs = {
	[](std::vector<double> v) { // 0
		return targetFunc->perform(v);
	},
	[](std::vector<double> v) { // 1
		return v[0] * v[0] + sqrt(abs(cos(fmod(v[0], 4))));
	},
	[](std::vector<double> v) { // 2
		return 2 / v[0] + v[0] * v[0] / 5 + v[0] / 3 - 5;
	},
	[](std::vector<double> v) { // 3
		return double(rand() % 100 - 50);
	},
	[](std::vector<double> v) { // 4
		return std::max(sin(v[0]), cos(v[0])) * std::max(tan(v[0]), atan(v[0]));
	},
	[](std::vector<double> v) { // 5
		return pow(1.075, v[0] + sin(v[0]) * 5);
	},
	[](std::vector<double> v) { // 6
		double x = v[0], a = v[1], b = v[2], c = v[3];
		return a * x * x + b * x + c;
	},
	[](std::vector<double> v) { // 7
		double x = v[0];
		return 0.1 * x * x + 0.5 * x + 2;
	},
	[](std::vector<double> v) { // 8
		double v0 = v[0], t = v[1], a = v[2];
		return v0 * t + a * t * t / 2;
	},
	[](std::vector<double> v) { // 9
		double x = v[0];
		return fmod(10 * x, x * x);
	},
	[](std::vector<double> v) { // 10
		int n = std::max(int(v[0]), 0);

		int* a = new int[std::max(n + 1, 3)];
		a[0] = 1;
		a[1] = 1;
		for (int i = 2; i < n + 1; i++)
			a[i] = a[i - 1] + a[i - 2];
		double out = a[n];
		delete[] a;
		return out;
	},
	[](std::vector<double> v) { // 11
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
		return double(out);
	},
	[](std::vector<double> v) { // 12
		double x = v[0], a = v[1], b = v[2], c = v[3];
		return a + b / (x + c);
	},
	[](std::vector<double> v) { // 13
		double x = v[0], a = v[1], b = v[2];
		return a * x + b;
	},
	[](std::vector<double> v) { // 14
		double x = v[0];
		return 2 * sin(x);
	},
};
