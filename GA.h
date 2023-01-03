#pragma once

#include <vector>
#include <list>

#include "Equation.h"
#include "Global.h"
#include "BaseGA.h"
#include "UseFunctions.h"
#include "PingPongSelection.h"

void init(int type = 0);

extern void (*createPreset)();
extern void (*createParents)();
extern void (*processGeneration)(); // ~perform

extern void (*display)(int num, int width, int height);
extern void (*displayInfo)(Expression* e, bool detail);

const std::vector<std::vector<void*>> GAfunctions = {
	{f_createPreset, f_createParents, f_processGeneration, f_display, f_displayInfo},
	{p_createPreset, f_createParents, p_processGeneration, p_display, p_displayInfo},
};