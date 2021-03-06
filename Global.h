#pragma once

#include <vector>
#include <array>
class Var;
class Member;
#include "Equation.h"

extern int const presetsCount;
const int parentsCount = 250;
const int generationSize = 5000;
const int maxMemberQuantity = 10;
const double increasingMutability = 5;
const double maxMutability = 150;
const double minMutability = 5;
const double mScoreInfluence = 0.05;
const double maxScore = 5;
const double minScore = -30;
const int expectedSize = 5;
const double sizeInfluence = 50;
const double outInfluence = 1;

extern std::vector<Var>& members;
extern std::vector<std::vector<Var>> presets;
extern std::array<double, presetsCount> expectedResults;
extern int nowPreset;
extern double mutationCount;
extern double mScore;

extern std::array<Member*, parentsCount> parents;
extern std::array<Member*, generationSize> generation;