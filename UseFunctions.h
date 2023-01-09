#pragma once

#include "Equation.h"
#include "Global.h"
#include "BaseGA.h"

void f_createPreset();
void f_createParents();
void f_processGeneration(); // ~perform + fitness
void f_regulator(bool detail);

void f_draw(Expression* e, float scale, int width = 237, int height = 60, int offsetX = 0, int offsetY = 0);
void f_display(int num, int width = 237, int height = 60);
void f_displayInfo(Expression* e, bool detail = false);

const bool generateFuncPreset = true;
const bool randFuncPresets = false;

extern float minVar;
extern float maxVar;
extern int funcNumber;
extern Member* targetFunc;

extern std::vector<float(*)(std::vector<float>)> funcs;