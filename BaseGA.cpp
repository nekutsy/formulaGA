#include "BaseGA.h"

std::vector<void (*)(Expression*)> m_funcs = {
	[](Expression* m) { // add member
		if (rand() % 2)
			m->members.push_back(randMember(2 + rand() % 4));
		else if (rand() % 2)
			m->members.push_back(new Const(rand() % constants.size()));
		else
			m->members.push_back(new Var(rand() % varCount));
		m->resize();
	},[](Expression* m) { // delete member
		int dm = rand() % m->mSize;
		m->members[dm]->~Member();
		delete m->members[dm];
		m->members.erase(m->members.begin() + dm);
		m->resize();
	},[](Expression* m) { // change operation 
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

void createGeneration(int x1, int x2) {
	int childCount = generationSize / parentsCount;
	for (int i = x1 * parentsCount / generationSize; i < x2 * parentsCount / generationSize; i++) {
		for (int j = 0; j < childCount; j++) {
			Member* child = duplicate(parents[i]);
			for (int k = 0; k < mutationCount; k++)
				mutate(child);
			generation[i * childCount + j] = child;
		}
	}
}

void performGeneration(int x1, int x2) {
	for (int i = x1; i < x2; i++) {
		generation[i]->perform();
		generation[i]->fitness();
	}
}

void selection(int x1, int x2) {
	for (int i = x1; i < x2; i++) {
		float fitn = generation[i]->fitn;
		for (int j = 0; j < parentsCount; j++) {
			mu_parents[j / threadCount].lock();
			if (fitn > parents[j]->fitn) {
				mu_parents[j / threadCount].unlock();
				bool unique = true;
				for (int k = 0; k < parentsCount && unique; k++) {
					mu_parents[k / threadCount].lock();
					unique = !((*generation[i]) == (*parents[k]));
					mu_parents[k / threadCount].unlock();
				}
				if (unique) {
					mu_parents[j / threadCount].lock();
					delete parents[j];
					parents[j] = generation[i];
					generation[i] = 0;
					mu_parents[j / threadCount].unlock();
				}
				break;
			}
			else
				mu_parents[j / threadCount].unlock();
		}
		if (generation[i])
			delete generation[i];
	}
}

void multithreadUse(void (*func)(int, int)) {
	const int fPerThread = generationSize / threadCount;
	std::thread thr[threadCount];
	for (int i = 0; i < threadCount; i++)
		thr[i] = std::thread(func, i * fPerThread, (i + 1) * fPerThread);

	for (int i = 0; i < threadCount; i++)
		thr[i].join();
}

void multithreadedSelection() {
	if (!useParents)
		for (int i = 0; i < parentsCount; i++)
			parents[i]->fitn = std::numeric_limits<float>::lowest();
	maxFitness = std::numeric_limits<float>::lowest();

	multithreadUse(selection);

	avgFitness = 0;
	for (int i = 0; i < parentsCount; i++) {
		float fitn = parents[i]->fitn;
		avgFitness += fitn;
		maxFitness = std::max(fitn, maxFitness);
	}
	avgFitness /= parentsCount;
}

void multithreadedPerform() {
	multithreadUse(performGeneration);
}
void multithreadedCreateGeneration() {
	multithreadUse(createGeneration);
}

void mutate(Member* m) {
	Member* p = 0;
	Member* changingM = getAbsoluteMember(m, rand() % m->size, p);
	Expression* parent = dynamic_cast<Expression*>(p);
	int chMnum = 0;
	if (parent) {
		chMnum = rand() % parent->members.size();
		changingM = parent->members[chMnum];
	}
	if (changingM->operation < 0)
		if (rand() % 2 || !parent)
			if (changingM->operation == -1)
				(dynamic_cast<Const*>(changingM))->mType = rand() % constants.size();
			else
				(dynamic_cast<Var*>(changingM))->mType = rand() % varCount;
		else {
			delete changingM;
			parent->members.erase(parent->members.begin() + chMnum);
			parent->members.push_back(randMember(1 + rand() % 5, 1 + rand() % 3));
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
		m_funcs[actionType](dynamic_cast<Expression*>(changingM));
	}
}