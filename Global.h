#pragma once

#include <vector>
#include <array>
class Var;
class Member;
#include "Equation.h"

const int parentsCount = 100;
const int generationSize = 1000;
const int maxMemberQuantity = 10;
const int expectedSize = 3;
const double sizeInfluence = 0.01;
const double outInfluence = 100;
const double unevenInfluence = 0.1;
const double nanPenalty = -10000;
const bool useParents = true;

const bool useFuncPreset = true;
const int funcPresetsCount = 100;
const int varFuncsPresetCount = 1;
const double minFuncPresetVar = -50;
const double maxFuncPresetVar = 50;

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

//pi* (pi)* (-1)* (10 / (pi) / (pi) / (x) / (1) / (2))* (1)* (2)* (2)* (10 + (pi)+(2) + (2) + (10) + (2) + (-1) + (2))* (-1)* (1 ^ (2) ^ (-1) ^ (pi) ^ (x) ^ (pi) ^ (1) ^ (10) ^ (x) ^ (pi) ^ (x))* (x / (x) / (1) / (-1) / (x))* (2 * (2) * (1) * (1) * (pi) * (1) * (2) * (-1) * (pi) * (pi) * (2))* (-1);
