#pragma once

#include "Equation.h"

void createGeneration(int x1 = 0, int x2 = parentsCount);
void multithreadedCreateGeneration();

void performGeneration(int x1 = 0, int x2 = generationSize);
void multithreadedPerform();

void selection(int x1 = 0, int x2 = generationSize);
void multithreadedSelection();

void mutate(Member* m);

extern std::vector<void (*)(Expression*)> m_funcs;