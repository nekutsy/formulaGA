#pragma once

#include "Equation.h"
#include "BaseGA.h"

const float mWidth = 60;
const float mHeight = 15;
const float pMaxSpeed = 2;
const float pAcceleration = 1;
const float pDeceleration = 0.75;
const float maxSpeed = 1.5;
const float durationLimit = 235;
//bool draw = false;

int p_pingpong(Expression* m1, Expression* m2, double& fitn1, double& fitn2, bool draw);
void p_drawScene(float pos1, float pos2, float x, float y, float pWidth);

void p_createPreset();
//void p_createParents();
void p_processGeneration(); // ~perform + fitness

void p_display(int num, int width = 237, int height = 60);
void p_displayInfo(Expression* e, bool detail = false);