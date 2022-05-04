#pragma once

#include <vector>
#include <list>

#include "Equation.h"

static std::vector<Var> members = {
	Var(1, "1"),
	Var(2, "2")
};

const double expectedResult = 1;
const int parentsCount = 10;
const int generationSize = 100;
const int maxMemberQuantity = 10;

extern std::vector<Member*> parents;
extern std::vector<Member*> generation;
extern std::vector<Var> result;
extern std::vector<double> rating;

void createGeneration();
void performGeneration();
void selection();

