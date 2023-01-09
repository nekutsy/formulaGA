#include "GA.h"

#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <iomanip> 

#include "Global.h"
#include "PingPongSelection.h"

void (*createPreset)();
void (*createParents)();
void (*processGeneration)();
void (*regulator)(bool detail);
void (*display)(int num, int width, int height);
void (*displayInfo)(Expression* e, bool detail);

void init(int type) {
	createPreset = (void(*)())GAfunctions[type][0];
	createParents = (void(*)())GAfunctions[type][1];
	processGeneration = (void(*)())GAfunctions[type][2];
	regulator = (void(*)(bool detail))GAfunctions[type][3];
	display = (void(*)(int, int, int))GAfunctions[type][4];
	displayInfo = (void(*)(Expression*, bool))GAfunctions[type][5];
}