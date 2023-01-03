#include "PingPongSelection.h"

#include <vector>
#include <iostream>

int p_pingpong(Expression* m1, Expression* m2, double& fitn1, double& fitn2, bool draw) {
	m1->fitn = -std::pow(expectedSize - m1->size, 2);
	m2->fitn = -std::pow(expectedSize - m2->size, 2);
	float pWidth = 10, p1 = mWidth / 2.f, p2 = mWidth / 2.f, v1 = 0, v2 = 0, x = mWidth / 2.f, y = 5, vx = 0.75 * (1 - 2 * (rand() % 2)), vy = 1;
	bool isRun = true, winner = false;
	int stepNum = 0, f1 = 0, f2 = 0;
	while (isRun) {
		if (mHeight < y + vy) {
			float _x = x + (mHeight - y) / vy * vx;
			if (_x >= p2 - pWidth - 1.0 && _x <= p2 + pWidth + 1.0) {
				vx += v2 * 0.25;
				y = mHeight;
				v2 += (2.0 * (rand() % 2) - 1.0);
			}
			else {
				//isRun = false;
				fitn2 -= 30.0;
				winner = false;
			}
			pWidth -= 0;
			vy = -vy;
		}
		if (0 > y + vy) {
			float _x = x + y / vy * vx;
			if (_x >= p1 - pWidth - 1.0 && _x <= p1 + pWidth + 1.0) {
				vx += v1 * 0.25;
				y = 0;
				v1 += (2.0 * (rand() % 2) - 1.0);
			}
			else {
				//isRun = false;
				fitn1 -= 30.0;
				winner = false;
			}
			pWidth -= 0;
			vy = -vy;
		}
		if (x + vx > mWidth) {
			vx = -vx * 1.1;
			x = mWidth;
		}
		if (x + vx < 0) {
			vx = -vx * 1.1;
			x = 0;
		}
		vx = std::min(maxSpeed, std::max(-maxSpeed, vx));
		x += vx;
		y += vy;

		std::vector<double> vars = { x, y, vx, vy, p1, v1 };
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

		v1 -= pDeceleration * (2 * (v1 > 0) - 1);
		v2 -= pDeceleration * (2 * (v2 > 0) - 1);

		p1 += v1;
		p2 += v2;

		p1 = std::max(pWidth, std::min(mWidth - pWidth, p1));
		p2 = std::max(pWidth, std::min(mWidth - pWidth, p2));

		if (p1 == pWidth || p1 == mWidth - pWidth) {
			v1 = -v1 * 0.5;
			fitn1 -= abs(v1) / 2.f + 1;
		}
		if (p2 == pWidth || p2 == mWidth - pWidth) {
			v2 = -v2 * 0.5;
			fitn2 -= abs(v2) / 2.f + 1;
		}

		if (isRun && draw) {
			system("cls");
			p_drawScene(p1, p2, x, y, pWidth);
		}
		stepNum += 1;
		if (stepNum > durationLimit)
			isRun = false;
	}
	/*if (winner) {
		m1->fitn = stepNum * 1.1 - std::pow(expectedSize - m1->size, 2);
		m2->fitn = stepNum - std::pow(expectedSize - m2->size, 2);
	}
	else {
		m2->fitn = stepNum * 1.1 - std::pow(expectedSize - m2->size, 2);
		m1->fitn = stepNum - std::pow(expectedSize - m1->size, 2);
	}*/

	return stepNum;
}

void p_drawScene(float pos1, float pos2, float x, float y, float pWidth) {
	pos1 = int(pos1);
	pos2 = int(pos2);

	std::cout << "|";
	for (int i = 0; i < pos1 - pWidth; i++)
		std::cout << " ";
	for (int i = 0; i < pWidth * 2; i++)
		std::cout << "#";
	for (int i = pos1 + pWidth; i < mWidth; i++)
		std::cout << " ";
	std::cout << "|" << std::endl;

	for (int i = 0; i < y; i++)
		std::cout << std::endl;

	for (int i = 0; i < x; i++)
		std::cout << " ";
	std::cout << "*";

	for (int i = std::round(y); i < mHeight; i++)
		std::cout << std::endl;

	std::cout << std::endl << "|";
	for (int i = 0; i < pos2 - pWidth; i++)
		std::cout << " ";

	for (int i = 0; i < pWidth * 2; i++)
		std::cout << "#";
	for (int i = pos2 + pWidth; i < mWidth; i++)
		std::cout << " ";
	std::cout << "|" << std::endl;
}

void p_createPreset() {
	varCount = 6;
	presetsCount = 0;
}
void p_processGeneration() {
	for (int i = 0; i < generationSize; i += 2) {
		Expression* e1 = dynamic_cast<Expression*>(generation[i]);
		Expression* e2 = dynamic_cast<Expression*>(generation[i + 1]);
		p_pingpong(e1, e2, e1->fitn, e2->fitn, false);
	}
	return;
	double _ = 0;
	for (int i = 0; i < generationSize; i += 2) {
		Expression* e = dynamic_cast<Expression*>(generation[i]);
		p_pingpong(e, e, e->fitn, e->fitn, false);
	}
}

void p_display(int num, int width, int height) {
	int num2;
	std::cout << "num2: ";
	std::cin >> num2;
	Expression* e1 = dynamic_cast<Expression*>(parents[num]);
	Expression* e2 = dynamic_cast<Expression*>(parents[num2]);
	double _ = 0;
	int duration = p_pingpong(e1, e2, _, _, true);
	std::cout << parents[num]->getName() << std::endl;
	std::cout << parents[num2]->getName() << std::endl;
	std::cout << "duration: " << duration << std::endl;
}
void p_displayInfo(Expression* e, bool detail) {
	std::cout << e->getName() + " = y" << std::endl;
	if (detail) {
		std::cout << "fitness: " << e->fitn << std::endl;
		std::cout << "size: " << e->size << std::endl;
		std::cout << "duration: " << p_pingpong(e, e, e->fitn, e->fitn, false);
	}
}