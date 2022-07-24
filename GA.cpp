#include "GA.h"

#include <algorithm>
#include <iostream>
#include <math.h>

#include "Global.h"

std::vector<void (*)(Member*)> m_funcs = {
	[](Member* m) { // add member
		if (rand() % 2)
			m->members.push_back(randMember(2 + rand() % 4));
		else
			m->members.push_back(new Constant(rand() % members->size()));
		m->resize();
	},[](Member* m) { // delete member
		int dm = rand() % m->mSize;
		m->members[dm]->~Member();
		delete m->members[dm];
		m->members.erase(m->members.begin() + dm);
		m->resize();
	},[](Member* m) { // change operation 
		int operation = rand() % operationsCount;
		int min = op[operation].minMembers, max = op[operation].maxMembers;

		if (min > m->mSize)
			m->members.resize(min);
		for (int i = m->mSize; i < min; i++)
			m->members[i] = randMember(1);
		m->resize();

		for (int i = max; i < m->mSize; i++) {
			m->members[i]->~Member();
			delete m->members[i];
		}
		if (max < m->mSize) {
			m->members.resize(max);
			m->resize();
		}
		m->operation = operation;
	},
};

void createPreset() {
	if (useFuncPreset) {
		presets.resize(funcPresetsCount);
		expectedResults.resize(funcPresetsCount);
		for (int i = 0; i < funcPresetsCount; i++) {
			int constSize = constants.size();
			presets[i] = new std::vector<Var>;
			presets[i]->resize(constSize + varFuncsPresetCount);
			Var* v = new Var[varFuncsPresetCount];

			for (int j = 0; j < constSize; j++)
				(*presets[i])[j] = constants[j];

			for (int j = 0; j < varFuncsPresetCount; j++) {
				std::string name = (j < variables[0].size()) ? variables[0][j].name : ("x" + char(65 + j));
				v[j] = Var(fmod(double((maxFuncPresetVar - minFuncPresetVar) / funcPresetsCount * i), (maxFuncPresetVar - minFuncPresetVar)) - minFuncPresetVar, name);
				(*presets[i])[constSize + j] = v[j];
			}
			expectedResults[i] = funcs[funcNumber](v);
		}
		presetsCount = funcPresetsCount;
	} else {
		presets.resize(presetsCount);
		for (int i = 0; i < presetsCount; i++) {
			int constSize = constants.size(), varSize = variables.size();
			presets[i] = new std::vector<Var>;
			presets[i]->resize(constSize + varSize);
			for (int j = 0; j < constSize; j++)
				(*presets[i])[j] = constants[j];
			for (int j = constSize; j < varSize; j++)
				(*presets[i])[j] = variables[i][j - constSize];
		}
	}
	members = presets[0];
}

void createGeneration() {
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
	int operation = rand() % operationsCount, size = std::max(std::min(mSize, op[operation].maxMembers), op[operation].minMembers);
	std::vector<Member*> constants;
	constants.resize(size);
	for (int i = 0; i < size; i++)
		constants[i] = new Constant(rand() % members->size());
	return new Member(constants, operation);
}

void performGeneration() {
	for (int i = 0; i < generationSize; i++) {
		generation[i]->perform();
		generation[i]->fitness();
	}
}

void selection() {
	if (!useParents)
		for (int i = 0; i < parentsCount; i++) {
			parents[i]->~Member();
			delete parents[i];
			parents[i] = duplicate(generation[i]);
		}

	long double preMaxFitness = maxFitness;
	for (int i = 0; i < generationSize; i++) {
		long double fitn = generation[i]->fitn;
		maxFitness = std::max(fitn, maxFitness);
		for (int j = 0; j < parentsCount; j++) {
			if (fitn > parents[j]->fitn) {
				bool repeated = false;
				for (int k = 0; k < parentsCount && !repeated; k++) {
					bool match = true;
					for (int l = 0; l < presetsCount; l++)
						match &= (generation[i]->results[l].value == parents[k]->results[l].value);
					repeated = (generation[i]->results[0].name == parents[k]->results[0].name) || match;
				}
				if (!repeated) {
					parents[j]->~Member();
					delete parents[j];
					parents[j] = generation[i];
					generation[i] = 0;
					break;
				}
			}
		}
		if (generation[i]) {
			generation[i]->~Member();
			delete generation[i];
		}
	}
	avgFitness = 0;
	for (int i = 0; i < parentsCount; i++)
		avgFitness += parents[i]->fitness();
	avgFitness /= parentsCount;
}

void mutate(Member* m) {
	Member* changingM = getMember(m, rand() % m->size);
	if (changingM->operation == -1)
		(dynamic_cast<Constant*>(changingM))->mType = rand() % members->size();
	else {
		bool deleteM = changingM->size > 1 && changingM->mSize > op[changingM->operation].minMembers,
			addM = changingM->mSize < op[changingM->operation].maxMembers;
		int actionType;
		if ((deleteM || addM) && rand() % 3)
			actionType = addM && (rand() % 2 || !deleteM);
		else
			actionType = 2;
		m_funcs[actionType](changingM);
	}
}