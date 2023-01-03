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

void multithreadedCreateGeneration() {
	const int fPerThread = parentsCount / generationThrCnt;
	std::thread thr[generationThrCnt];
	for (int i = 0; i < generationThrCnt; i++)
		thr[i] = std::thread(createGeneration, i * fPerThread, (i + 1) * fPerThread);

	for (int i = 0; i < generationThrCnt; i++)
		thr[i].join();
}

void createGeneration(int x1, int x2) {
	int childCount = generationSize / parentsCount;
	for (int i = x1; i < x2; i++) {
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

void multithreadedPerform() {
	const int fPerThread = generationSize / performThrCnt;
	std::thread thr[performThrCnt];
	for (int i = 0; i < performThrCnt; i++)
		thr[i] = std::thread(performGeneration, i * fPerThread, (i + 1) * fPerThread);

	for (int i = 0; i < performThrCnt; i++)
		thr[i].join();
}

void selection(int x1, int x2) {
	for (int i = x1; i < x2; i++) {
		long double fitn = generation[i]->fitn;
		for (int j = 0; j < parentsCount; j++) {
			mu_parents.lock();
			if (fitn > parents[j]->fitn) {
				mu_parents.unlock();
				bool unique = true;
				for (int k = 0; k < parentsCount && unique; k++) {
					bool identity = true;
					bool improv = true;
					mu_parents.lock();
					if (fitn <= parents[k]->fitn)
						improv = false;
					for (int l = 0; l < presetsCount && (identity || improv); l++) {
						if (generation[i]->getResult(l) != parents[k]->getResult(l))
							identity = false;
					}
					mu_parents.unlock();
					unique = !identity || improv;
				}
				if (unique) {
					mu_parents.lock();
					delete parents[j];
					parents[j] = generation[i];
					generation[i] = 0;
					mu_parents.unlock();
				}
				break;
			}
			else
				mu_parents.unlock();
		}
		if (fitn > maxFitness)
			maxFitness = fitn;
		if (generation[i])
			delete generation[i];
	}
}

void multithreadedSelection() {
	if (!useParents)
		for (int i = 0; i < parentsCount; i++)
			parents[i]->fitn = std::numeric_limits<long double>::lowest();

	const int fPerThread = generationSize / selectionThrCnt;
	std::thread thr[selectionThrCnt];

	maxFitness = std::numeric_limits<double>::lowest();
	for (int i = 0; i < selectionThrCnt; i++)
		thr[i] = std::thread(selection, i * fPerThread, (i + 1) * fPerThread);

	for (int i = 0; i < selectionThrCnt; i++)
		thr[i].join();

	avgFitness = 0;
	for (int i = 0; i < parentsCount; i++)
		avgFitness += parents[i]->fitn;
	avgFitness /= parentsCount;
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