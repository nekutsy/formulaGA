#pragma once

#include "Equation.h"

void createGeneration(int x1 = 0, int x2 = parentsCount);
void performGeneration(int x1 = 0, int x2 = generationSize);
void selection(int x1 = 0, int x2 = generationSize);

void multithreadUse(void (*func)(int, int));
void multithreadedCreateGeneration();
void multithreadedPerform();
void multithreadedSelection();

void mutate(Member* m);

extern std::vector<void (*)(Expression*)> m_funcs;