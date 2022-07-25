#pragma once

#include <vector>
#include <array>
class Var;
class Member;
#include "Equation.h"

const int parentsCount = 100;
const int generationSize = 1000;
const int maxMemberQuantity = 10;
const int expectedSize = 1;
const double sizeInfluence = 0.1;
const double outInfluence = 1000;
const double unevenInfluence = 0.01;
const double nanPenalty = -10000000;
const bool useParents = true;

const bool useFuncPreset = true;
const bool randFuncPresets = false;
const int funcPresetsCount = 100;
const int varFuncsPresetCount = 1;
const double minFuncPresetVar = -25;
const double maxFuncPresetVar = 25;

extern int presetsCount;
extern std::vector<Var> constants;
extern std::vector<std::vector<Var>> variables;
extern std::vector<double (*)(Var*)> funcs;
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