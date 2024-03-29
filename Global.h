#pragma once

#include <vector>
#include <array>
#include <mutex>

class Member;

#include "Equation.h"

const int parentsCount = 128;
const int generationSize = 4096;
extern const int constCount;
const int threadCount = 8;
const int mutexCount = parentsCount / threadCount;

const int r_period = 40;
const float r_baseMutation = 25;
const float r_mutationInfluence = 25;
const float r_baseExpectedSize = 15;
const float r_baseOut = 15;
const float r_baseUneven = 15;

extern int expectedSize;
extern float sizeMultiplier;
extern float outMultiplier;
extern float unevenMultiplier;
extern float nanPenalty;
extern float nanBonus;
extern bool useParents;

extern int stepNum;
extern float mutationCount;
extern float avgFitness;
extern float maxFitness;

extern int presetsCountPerVar;
extern int varCount;
extern int presetsCount;

extern std::vector<float> constants;
extern std::vector<std::string> constantNames;

extern std::vector<std::string> varNames;
extern std::vector<float> varValues;

extern std::vector<std::vector<float>> presets;
extern std::vector<float> expectedResults;

extern std::array<Member*, parentsCount> parents;
extern std::array<Member*, generationSize> generation;
extern std::array<std::mutex, mutexCount> mu_parents;

//extern std::mutex mu_parents;