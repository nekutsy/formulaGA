#include "GA.h"

#include <algorithm>
#include <iostream>
#include <math.h>

#include "Global.h"

double fitness(Member* m) {
	double sizeW = 0, outW = 0;
	int preset = nowPreset;
	for (int i = 0; i < presetsCount; i++) {
		swapPreset(i);
		sizeW += -pow(m->size - expectedSize, 4) * sizeInfluence;
		outW += -pow(expectedResults[nowPreset] - m->results[i].value, 2) * outInfluence;
	}
	swapPreset(preset);
	return sizeW + outW;
}

void createGeneration() {
	mScore = std::min(std::max(mScore, minScore), maxScore);
	mutationCount += increasingMutability * -(mScore) * mScoreInfluence;
	mutationCount = std::max(mutationCount, minMutability);
	mutationCount = std::min(mutationCount, maxMutability);
	//std::cout << "mutationsCount: " << mutationCount << std::endl;
	std::cout << "mScore: " << mScore << std::endl;

	int childCount = generationSize / parentsCount;
	for (int i = 0; i < parentsCount; i++) {
		for (int j = 0; j < childCount; j++) {
			Member* child = duplicate(parents[i]);
			for (int k = 0; k < mutationCount; k++)
				mutate(child);
			generation[i * childCount + j] = child;
		}
	}
}

Member* randMember(int mSize) {
	std::vector<Member*> constants;
	constants.resize(mSize);
	for (int i = 0; i < mSize; i++)
		constants[i] = new Constant(rand() % members.size());
	return new Member(constants, rand() % operationsCount);
}

void performGeneration() {
	for (int i = 0; i < generationSize; i++)
		generation[i]->perform();
}

void selection() {
	double dmScore = 0;
	for (int i = 0; i < generationSize; i++) {
		bool isImproved = false;
		for (int j = 0; j < parentsCount; j++) {
			if (fitness(generation[i]) > fitness(parents[j])) {
				isImproved = true;
				parents[j]->~Member();
				delete parents[j];
				parents[j] = duplicate(generation[i]);
				break;
			}
		}
		generation[i]->~Member();
		delete generation[i];

		dmScore -= (1 - isImproved * 3);
	}
	mScore += dmScore / generationSize + 0.789;
}

void mutate(Member* m) {
	int mCount = m->size;
	Member* changingM;
	do {
		changingM = getMember(m, rand() % mCount);
	} while (changingM->operation == -1 && rand() % 5);

	if (changingM->operation == -1) {
		int actionType = rand() % 1;
		
		switch (actionType) {
		case 0:
			(dynamic_cast<Constant*>(changingM))->mType = rand() % members.size();
		}
	}
	else {
		int actionType = rand() % (operationsCount + 2);
		if (changingM->mSize > 2)
			actionType += rand() % 2;

		switch (actionType) { // add constant
		case operationsCount: {
			changingM->members.push_back(new Constant(rand() % members.size()));
			changingM->resize();
			break;
		}
		case operationsCount + 1: { // add member
			changingM->members.push_back(randMember(2 + rand() % 10));
			changingM->resize();
			break;
		}
		case operationsCount + 2: { // delete member
			int dm = rand() % changingM->mSize;
			changingM->members[dm]->~Member();
			delete changingM->members[dm];
			changingM->members.erase(changingM->members.begin() + dm);

			changingM->resize();
			break;
		}
		default:
			changingM->operation = actionType;
			break;
		}
	}
}
