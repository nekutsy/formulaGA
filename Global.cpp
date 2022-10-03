#include "Global.h"

#include <math.h>

int presetsCount;
double mutationCount = 10;
int nowPreset = 0;
double mScore = 5;
long double avgFitness = 0;
long double maxFitness = std::numeric_limits<long double>::lowest();
std::vector<Var>* members;
int funcNumber = 6;

std::vector<Var> constants = {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	Var(10, "10"),
	//Var(3.14, "pi"),
};

std::vector<std::string> varNames = {
	"a",
	"b",
	"c",
	"d",
	"e",
	"k",
};

std::vector<std::vector<Var>> variables = {
	{
	Var(-2, "x"),
	Var(-2, "y"),
	Var(2, "Fx"),
	Var(2, "Fy"),
	},{
	Var(1, "x"),
	Var(-2, "y"),
	Var(-3, "Fx"),
	Var(2, "Fy"),
	},{
	Var(-1, "x"),
	Var(-3, "y"),
	Var(1.25, "Fx"),
	Var(2.5, "Fy"),
	},{
	Var(2, "x"),
	Var(-1.25, "y"),
	Var(-3, "Fx"),
	Var(0.5, "Fy"),
	},{
	Var(3, "x"),
	Var(-3, "y"),
	Var(-3.5, "Fx"),
	Var(3.5, "Fy"),
	},{
	Var(5, "x"),
	Var(2, "y"),
	Var(-6, "Fx"),
	Var(-3, "Fy"),
	},{
	Var(-2, "x"),
	Var(-2, "y"),
	Var(1.25, "Fx"),
	Var(2.5, "Fy"),
	},
};

std::vector<double> expectedResults = { -1, -0.5, 0, 0.5, 1, 1, 1, 0.5, 0, -0.5, -1, -1 };

std::vector<double (*)(std::vector<Var>)> funcs = {
	[](std::vector<Var> v) {
		return sin(v[0].value / 5) * 5;
	},
	[](std::vector<Var> v) {
		return v[0].value * v[0].value + sqrt(cos(fmod(v[0].value, 4)));
	},
	[](std::vector<Var> v) {
		return fmod(v[0].value * 10, 10 / v[0].value);
	},
	[](std::vector<Var> v) {
		return double(rand() % 100 - 50);
	},
	[](std::vector<Var> v) {
		return std::max(sin(v[0].value), cos(v[0].value)) * std::max(tan(v[0].value), atan(v[0].value));
	},
	[](std::vector<Var> v) {
		return pow(1.075, v[0].value + sin(v[0].value));
	},
	[](std::vector<Var> v) {
		double x = v[0].value, a = v[1].value, b = v[2].value, c = v[3].value;
		return a * x * x + b * x + c;
	},
};

std::vector<std::vector<Var>*> presets = {
	new std::vector<Var>({
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	Var(10, "10"),
	
	Var(-2, "x"),
	Var(-2, "y"),
	Var(2, "Fx"),
	Var(2, "Fy"),
}),
};

std::array<Member*, parentsCount> parents;
std::array<Member*, generationSize> generation;