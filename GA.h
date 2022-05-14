#pragma once

#include <vector>
#include <list>

#include "Equation.h"

void createGeneration();
void mutate(Member* m);
Member* randMember(int mSize);

void performGeneration();

void selection();
double fitness(Member*);

