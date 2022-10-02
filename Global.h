#pragma once

#include <vector>
#include <array>
class Var;
class Member;
#include "Equation.h"

const int parentsCount = 100;
const int generationSize = 500;
const int maxMemberQuantity = 10;
const int expectedSize = 2;
const double sizeInfluence = 0.5;
const double outInfluence = 100;
const double unevenInfluence = 0.5;
const double nanPenalty = std::numeric_limits<double>::lowest() / 10;
const bool useParents = true;

const bool generateFuncPreset = true;
const bool randFuncPresets = false;
//const int funcPresetsCount = 200;
const int funcPresetsPerVar = 50;
const int varFuncsPresetCount = 3;
const double minFuncPresetVar = -10;
const double maxFuncPresetVar = 10;

extern int presetsCount;
extern std::vector<Var> constants;
extern std::vector<std::vector<Var>> variables;
extern std::vector<std::string> varNames;
extern std::vector<double(*)(std::vector<Var>)> funcs;
extern int funcNumber;

extern std::vector<Var>* members;
extern std::vector<std::vector<Var>*> presets;
extern std::vector<double> expectedResults;
extern int nowPreset;
extern double mutationCount;
extern long double avgFitness;
extern long double maxFitness;

extern std::array<Member*, parentsCount> parents;
extern std::array<Member*, generationSize> generation;