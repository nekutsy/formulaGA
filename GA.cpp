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
			m->members.push_back(new Constant(rand() % g_members->size()));
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

/*
void createPreset() {
	if (generateFuncPreset) {
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
				double x;
				if (randFuncPresets) {
					x = fmod(double(rand()) / double(rand()) * double(rand()), maxFuncPresetVar - minFuncPresetVar) - minFuncPresetVar;
				} else {
					x = (maxFuncPresetVar - minFuncPresetVar) / double(funcPresetsCount) * double(i) - minFuncPresetVar;
				} //double((maxFuncPresetVar - minFuncPresetVar) / funcPresetsCount * i), (maxFuncPresetVar - minFuncPresetVar)) - minFuncPresetVar
				v[j] = Var(x, name);
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
}*/

void createPreset() {
	int constSize = constants.size();
	if (generateFuncPreset) {
		presetsCount = varFuncsPresetCount * funcPresetsPerVar;
		presets.resize(presetsCount);
		expectedResults.resize(presetsCount);
		for (int i = 0; i < funcPresetsPerVar; i++) {
			for (int j = 0; j < varFuncsPresetCount; j++) {
				std::vector<Var>* preset = new std::vector<Var>;
				preset->resize(constSize + varFuncsPresetCount);
				for (int k = 0; k < constSize; k++)
					(*preset)[k] = constants[k];

				for (int k = constSize; k < preset->size(); k++) {
					std::string name;
					if (k - constSize >= varNames.size())
						name = "var" + std::to_string(k - constSize);
					else
						name = varNames[k - constSize];
					(*preset)[k] = Var(minFuncPresetVar + (maxFuncPresetVar - minFuncPresetVar) / funcPresetsPerVar * i, name);
				}
				/*std::cout << "func(" << (*preset)[0].name << "(" << (*preset)[0].value << ")";
				for (int iii = 1; iii < preset->size(); iii++)
					std::cout << ", " << (*preset)[iii].name << "(" << (*preset)[iii].value << ")";
				std::cout << ") = " << funcs[funcNumber](*preset) << std::endl;*/
				presets[i * varFuncsPresetCount + j] = preset;

				std::vector<Var> vec;
				vec.resize(varFuncsPresetCount);
				std::copy((*preset).begin() + constSize, (*preset).end(), vec.begin());
				expectedResults[i * varFuncsPresetCount + j] = funcs[funcNumber](vec);
			}

		}
	}
	else {
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
	g_members = presets[0];
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

Member* randMember(int mSize, int maxDeep) {
	int operation = rand() % operationsCount, size = std::max(std::min(mSize, op[operation].maxMembers), op[operation].minMembers);
	std::vector<Member*> constants;
	constants.resize(size);
	for (int i = 0; i < size; i++)
		if (maxDeep > 1 && rand() % 2)
			constants[i] = randMember(mSize, maxDeep - 1);
		else
			constants[i] = new Constant(rand() % g_members->size());

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

	for (int i = 0; i < generationSize; i++) {
		long double fitn = generation[i]->fitn;
		for (int j = 0; j < parentsCount; j++) {
			if (fitn > parents[j]->fitn) {
				bool unique = true;
				for (int k = 0; k < parentsCount && unique; k++) {
					bool identity = true;
					bool improv = true;
					for (int l = 0; l < presetsCount && (identity || improv); l++) {
						if (generation[i]->results[l] != parents[k]->results[l])
							identity = false;
						if (fitn <= parents[k]->fitn)
							improv = false;
					}
					unique = !identity || improv;
				}
				if (unique) {
					parents[j]->~Member();
					delete parents[j];
					parents[j] = generation[i];
					generation[i] = 0;
				}
				break;
			}
		}
		if (fitn > maxFitness) {
			maxFitness = fitn;
			//std::cout << generation[i] << std::endl;
		}
		if (generation[i]) {
			generation[i]->~Member();
			delete generation[i];
		}
	}
	avgFitness = 0;
	for (int i = 0; i < parentsCount; i++)
		avgFitness += parents[i]->fitn;
	avgFitness /= parentsCount;
}

void mutate(Member* m) {
	Member* parent = 0;
	Member* changingM = getMember(m, rand() % m->size, parent);
	int chMnum = 0;
	if (parent) {
		chMnum = rand() % parent->members.size();
		changingM = parent->members[chMnum];
	}
	if (changingM->operation == -1)
		if (rand() % 2 || !parent)
			(dynamic_cast<Constant*>(changingM))->mType = rand() % g_members->size();
		else {
			delete changingM;
			parent->members.erase(parent->members.begin() + chMnum);
			parent->members.push_back(randMember(1 + rand() % 5));
			parent->resize();
		}
	else {
		bool deleteM = changingM->mSize > 1 && changingM->mSize > op[changingM->operation].minMembers,
			addM = changingM->mSize < op[changingM->operation].maxMembers;
		int actionType;
		if ((deleteM || addM) && rand() % 3)
			actionType = addM && (rand() % 2 || !deleteM);
		else
			actionType = 2;
		m_funcs[actionType](changingM);
	}
}