#pragma once

#include "Equation.h"
#include "BaseGA.h"

extern float mWidth;
extern float mHeight;
extern float pMaxSpeed;
extern float pAcceleration;
extern float pDeceleration;
extern float maxSpeed;
extern float durationLimit;
extern int limitOfMisses;
extern float difficult;

const bool competition = false;
const int iterationCount = 3;
//bool draw = false;

int p_pong(Expression* m1, Expression* m2, float& fitn1, float& fitn2, bool draw);
int p_soloPong(Expression* m, float& fitn1);
void p_drawScene(float pos1, float pos2, float x, float y, int mr1, int mr2, float pWidth);

void p_createPreset();
//void p_createParents();
void p_processGeneration(int x1, int x2); // ~perform + fitness
void p_multithreadedProcessGeneration();
void p_regulator(bool detail);
void p_createParents();

void p_display(int num, int width = 237, int height = 60);
void p_displayInfo(Expression* e, bool detail = false);