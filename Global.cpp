#include "Global.h"

#include <math.h>

int presetsCountPerVar = 5;
int varCount = 4;
double minVar = -10;
double maxVar = 10;

int presetsCount = presetsCountPerVar * varCount;
double mutationCount = 50;
double mScore = 5;
double avgFitness = 0;
double maxFitness = std::numeric_limits<double>::lowest();
Member* maxFitnM = 0;
int funcNumber = 6;
Member* targetFunc;

std::vector<double> constants = {
	1, -1,
	2, -2,
	10, 5,
	0.1
	//3.14159265359,
};
std::vector<std::string> constantNames = {
	"1", "-1",
	"2", "-2",
	"10", "5",
	"0.1",
};
std::vector<std::vector<double>> variables;
std::vector<std::string> varNames = {
	"x", "y", "vx", "vy", "p1", "v1", "p2", "v2",
	"x", "a", "b", "c", "d", "e", "k", "l",
};

std::vector<double> expectedResults;

std::vector<double> varValues;
std::vector<std::vector<double>> presets;

std::mutex mu_parents;

std::array<Member*, parentsCount> parents;
std::array<Member*, generationSize> generation;
