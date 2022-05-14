#pragma once

#include <vector>
#include <array>
class Var;
class Member;
#include "Equation.h"

extern int const presetsCount;
const int parentsCount = 100;
const int generationSize = 200;
const int maxMemberQuantity = 10;
const float increasingMutability = 5;
const float maxMutability = 20;
const float minMutability = 5;
const float mScoreInfluence = 0.01;
const float maxScore = 5;
const float minScore = -1;

extern std::vector<Var>& members;
extern std::vector<std::vector<Var>> presets;
extern std::array<double, presetsCount> expectedResults;
extern int nowPreset;
extern float mutationCount;
extern float mScore;

extern std::array<Member*, parentsCount> parents;
extern std::array<Member*, generationSize> generation;