#include "Global.h"

#include <math.h>

int presetsCount = 7;
double mutationCount = 10;
int nowPreset = 0;
double mScore = 5;
long double avgFitness = 0;
long double maxFitness = std::numeric_limits<long double>::lowest();
std::vector<Var>* members;
int funcNumber = 2;

std::vector<Var> constants = {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	Var(10, "10"),
	Var(3.14, "pi"),
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

std::vector<double (*)(Var*)> funcs = {
	[](Var* v) {
		return sin(v->value);
	},
	[](Var* v) {
		return v->value * v->value + sqrt(cos(fmod(v->value, 4)));
	},
	[](Var* v) {
		return fmod(v->value, 13.7483259);
	},
	[](Var* v) {
		return double(rand() % 100 - 50);
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