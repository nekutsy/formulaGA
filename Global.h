#pragma once

#include <vector>
#include <array>
class Var;
class Member;
#include "Equation.h"

extern int const presetsCount;
const int parentsCount = 1000;
const int generationSize = 10000;
const int maxMemberQuantity = 10;
const double increasingMutability = 5;
const double maxMutability = 20;
const double minMutability = 5;
const double mScoreInfluence = 0.01;
const double maxScore = 15;
const double minScore = -15;
const int expectedSize = 5;
const double sizeInfluence = 0.125;
const double outInfluence = 500;

extern std::vector<Var>& members;
extern std::vector<std::vector<Var>> presets;
extern std::array<double, presetsCount> expectedResults;
extern int nowPreset;
extern double mutationCount;
extern double mScore;

extern std::array<Member*, parentsCount> parents;
extern std::array<Member*, generationSize> generation;