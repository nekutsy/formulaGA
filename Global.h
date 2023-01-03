#pragma once

#include <vector>
#include <array>
#include <mutex>

class Member;

#include "Equation.h"

const int parentsCount = 500;
const int generationSize = 5000;
const int expectedSize = 40;
const double sizeMultiplier = 0.005;
const double outMultiplier = 1;
const double unevenMultiplier = 15;
const double nanPenalty = std::numeric_limits<float>::lowest();
const bool useParents = true;

const bool pingPongSelection = false;
const bool generateFuncPreset = true;
const bool randFuncPresets = false;
extern int presetsCountPerVar;
extern int varCount;
extern double minVar;
extern double maxVar;
extern std::vector<std::vector<double>> presetParametrs;

const int performThrCnt = 10;
const int selectionThrCnt = 10;
const int generationThrCnt = 10;

extern int presetsCount;
extern std::vector<double> constants;
extern std::vector<std::string> constantNames;
extern std::vector<std::vector<double>> variables;
extern std::vector<std::string> varNames;
extern int funcNumber;
extern bool customTargetFunc;
extern Member* targetFunc;

extern std::vector<double> varValues;
extern std::vector<std::vector<double>> presets;
extern std::vector<double> expectedResults;
extern double mutationCount;
extern double avgFitness;
extern double maxFitness;
extern Member* maxFitnM;

extern std::mutex mu_parents;
extern std::mutex mu_generation;

extern std::array<Member*, parentsCount> parents;
extern std::array<Member*, generationSize> generation;