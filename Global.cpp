#include "Global.h"

#include <math.h>

int expectedSize = 20;
float sizeMultiplier = -0.01;
float outMultiplier = -50;
float unevenMultiplier = -20;
float nanPenalty = -1000000000000;
float nanBonus = 1000000;
bool useParents = true;

int presetsCountPerVar = 1500;
int varCount = 1;

int presetsCount = presetsCountPerVar * varCount;
int stepNum = 0;
float mutationCount = 50;
float avgFitness = 0;
float maxFitness = std::numeric_limits<float>::lowest();
Member* maxFitnM = 0;

std::vector<float> constants = {
	1, -1,
	2, -2,
	3, -3,
	4, 5,
	6, 7,
	8, 9,
	10, 15,
	25, 100,
	0.5, 0.1,
};
const int constCount = constants.size();
std::vector<std::string> constantNames = {
	"1", "-1",
	"2", "-2",
	"3", "-3",
	"4", "5",
	"6", "7",
	"8", "9",
	"10", "15",
	"25", "100",
	"0.5", "0.1",
};

std::vector<float> varValues;
std::vector<std::string> varNames = {
	"x", "a", "b", "c", "d", "e", "k", "l",
};

std::vector<float> expectedResults;
std::vector<std::vector<float>> presets;

//std::mutex mu_parents;

std::array<Member*, parentsCount> parents;
std::array<Member*, generationSize> generation;
std::array<std::mutex, mutexCount> mu_parents;
