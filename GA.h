#pragma once

#include <vector>
#include <list>

#include "Equation.h"

void createPreset();
void createGeneration();
void mutate(Member* m);
Member* randMember(int mSize, int maxDeep = 1, int opType = -1);

void performGeneration();

void selection();
//long double fitness(Member*);

extern std::vector<void (*)(Member*)> m_funcs;