#include "PingPongSelection.h"

#define _USE_MATH_DEFINES

#include <vector>
#include <iostream>
#include <math.h>

float mWidth = 60;
float mHeight = 20;
float pMaxSpeed = 2;
float pAcceleration = 0.4;
float pDeceleration = 0.99;
float durationLimit = 900;
int limitOfMisses = 5;
float difficult = 1;

int p_pingpong(Expression* m1, Expression* m2, float& fitn1, float& fitn2, bool draw) {
	fitn1 = -std::pow(expectedSize - m1->size, 2);
	fitn2 = -std::pow(expectedSize - m2->size, 2);
	float pWidth = 7.5, p1 = mWidth / 2.f, p2 = mWidth / 2.f, v1 = 0, v2 = 0, x = mWidth / 2.f, y = 5, vx = 0.75 * (1 - 2 * (rand() % 2)), vy = 1;
	bool isRun = true;
	int stepNum = 0, f1 = 0, f2 = 0, missRemain1 = limitOfMisses / std::sqrt(difficult), missRemain2 = limitOfMisses / std::sqrt(difficult);
	while (isRun) {
		if (0 > y + vy) {
			float _x = x + y / vy * vx;
			if (_x >= p1 - pWidth - 1.0 && _x <= p1 + pWidth + 1.0) {
				vx += v1 * (0.1 + difficult * 0.05);
				vx *= 1 - 1.6 * (rand() % 7 == 0);
				vy *= 1 + difficult * 0.05;
				y = 0;
				v1 += difficult * (2 * (rand() % 2) - 1);
			}
			else {
				fitn1 -= 75 * (1 + 2 * difficult);
				fitn2 += 10 * (2 + 2 * difficult);
				missRemain1 -= 1;
				if (missRemain1 < 0)
					isRun = false;
			}
			pWidth -= difficult / 25.f;
			vy = -vy;
		}
		if (mHeight < y + vy) {
			float _x = x + (mHeight - y) / vy * vx;
			if (_x >= p2 - pWidth - 1.0 && _x <= p2 + pWidth + 1.0) {
				vx += v2 * (0.1 + difficult * 0.05);
				vx *= 1 - 1.6 * (rand() % 7 == 0);
				vy *= 1 + difficult * 0.05;
				y = mHeight;
				v2 += difficult * (2 * (rand() % 2) - 1);
			}
			else {
				fitn2 -= 75 * (1 + 2 * difficult);
				fitn1 += 10 * (1 + 2 * difficult);
				missRemain2 -= 1;
				if (missRemain2 < 0)
					isRun = false;
			}
			pWidth -= difficult / 25.f;
			vy = -vy;
		}
		vx = std::min((0.1f + difficult * 1.25f), std::max(-(0.1f + difficult * 1.25f), vx));
		vy = std::min(0.8f + difficult * 0.1f, std::max(-(0.8f + difficult * 0.1f), vy));

		if (x + vx > mWidth) {
			vx = -vx * (1 + difficult * 0.075);
			x = mWidth;
		}
		else
			x += vx;
		if (x + vx < 0) {
			vx = -vx * (1 + difficult * 0.075);
			x = 0;
		}
		else
			y += vy;

		std::vector<float> vars = { x, y, vx, vy, p1, v1 };
		float  dv1 = std::max(std::min(float(m1->perform(vars)) / 2.f, pAcceleration), -pAcceleration);
		if (dv1 * 0 == dv1 * 0)
			v1 += dv1;
		else
			fitn1 += nanPenalty;

		vars = { x, mHeight - y, vx, -vy, p2, v2 };
		float dv2 = std::max(std::min(float(m2->perform(vars)) / 2.f, pAcceleration), -pAcceleration);
		if (dv2 * 0 == dv2 * 0)
			v2 += dv2;
		else
			fitn2 += nanPenalty;

		v1 *= pDeceleration;
		v2 *= pDeceleration;
		v1 = std::min(std::max(v1, -pMaxSpeed), pMaxSpeed);
		v2 = std::min(std::max(v2, -pMaxSpeed), pMaxSpeed);

		p1 += v1;
		p2 += v2;
		p1 = std::max(pWidth, std::min(mWidth - pWidth, p1));
		p2 = std::max(pWidth, std::min(mWidth - pWidth, p2));

		if (p1 == pWidth || p1 == mWidth - pWidth) {
			v1 = -v1 / 2.f;
			fitn1 -= (abs(v1) / 2.f + 1) / difficult;
		}
		if (p2 == pWidth || p2 == mWidth - pWidth) {
			v2 = -v2 / 2.f;
			fitn2 -= (abs(v2) / 2.f + 1) / difficult;
		}

		if (isRun && draw) {
			system("cls");
			p_drawScene(p1, p2, x, y, missRemain1, missRemain2, pWidth);
		}
		stepNum += 1;
		if (stepNum > durationLimit)
			isRun = false;
	}
	fitn1 += stepNum;
	fitn2 += stepNum;
	return stepNum;
}

void p_drawScene(float pos1, float pos2, float x, float y, int mr1, int mr2, float pWidth) {
	/*pos1 = int(pos1);
	pos2 = int(pos2);
	x = int(x);
	y = int(y);
	pWidth = int(pWidth);*/

	std::cout << "|";
	for (int i = 0; i < int(pos1) - int (pWidth); i++)
		std::cout << " ";
	for (int i = 0; i < 2 * int(pWidth); i++)
		std::cout << "#";
	for (int i = int(pos1) + int (pWidth); i < int(mWidth); i++)
		std::cout << " ";
	std::cout << "| " << mr1 << std::endl;

	for (int i = 0; i < std::round(y); i++)
		std::cout << std::endl;

	for (int i = 0; i < int(x); i++)
		std::cout << " ";
	std::cout << "*";

	for (int i = std::round(y); i < std::round(mHeight); i++)
		std::cout << std::endl;

	std::cout << std::endl << "|";
	for (int i = 0; i < int(pos2) - int(pWidth); i++)
		std::cout << " ";

	for (int i = 0; i < 2 * int(pWidth); i++)
		std::cout << "#";
	for (int i = int(pos2) + int(pWidth); i < int(mWidth); i++)
		std::cout << " ";
	std::cout << "| " << mr2 << std::endl;
}

void p_createPreset() {
	varCount = 6;
	presetsCount = 0;
	varNames = { "x", "y", "vx", "vy", "p1", "v1", "p2", "v2" };
}

void p_processGeneration(int x1, int x2) {
	for (int i = x1; i < x2; i += 2) {
		Expression* e1 = dynamic_cast<Expression*>(generation[i]);
		Expression* e2 = dynamic_cast<Expression*>(generation[i + 1]);
		p_pingpong(e1, e2, e1->fitn, e2->fitn, false);
	}
	for (int i = x1 * parentsCount / generationSize; i < x2 * parentsCount / generationSize; i += 2) {
		Expression* e1 = dynamic_cast<Expression*>(parents[i]);
		Expression* e2 = dynamic_cast<Expression*>(parents[i + 1]);
		p_pingpong(e1, e2, e1->fitn, e2->fitn, false);
	}
}

void p_multithreadedProcessGeneration() {
	multithreadUse(p_processGeneration);
}

void p_regulator(bool detail) {
	mutationCount = std::max(r_baseMutation + sin(stepNum * M_PI / r_period) * r_mutationInfluence, 1.0);
	difficult = std::max(std::min(0.8 + std::sqrt(2 * stepNum) * 0.04, 2.5), 1.0);
	mWidth += 0.05 / (0.9 + stepNum / 75.0);
	//durationLimit += 1;
	if (detail) {
		std::cout << "mutationCount: " << mutationCount << std::endl;
		std::cout << "difficult: " << difficult << std::endl;
		//std::cout << "durationLimit: " << durationLimit << std::endl;
		std::cout << "mWidth: " << mWidth << std::endl;
		std::cout << std::endl;
	}
}

void p_display(int num, int width, int height) {
	int num2;
	std::cout << "num2: ";
	std::cin >> num2;
	Expression* e1 = dynamic_cast<Expression*>(parents[num]);
	Expression* e2 = dynamic_cast<Expression*>(parents[num2]);
	float _ = 0;
	int duration = p_pingpong(e1, e2, _, _, true);
	p_displayInfo(e1, false);
	p_displayInfo(e2, false);
	std::cout << "duration: " << duration << std::endl;
}

void p_displayInfo(Expression* e, bool detail) {
	std::cout << e->getName() + " = y" << std::endl;
	std::cout << "fitness: " << e->fitn << std::endl;
	if (detail) {
		std::cout << "size: " << e->size << std::endl;
		float _ = 0;
		std::cout << "duration: " << p_pingpong(e, e, _, _, false) << std::endl;
	}
}