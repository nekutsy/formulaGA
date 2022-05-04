#include "GA.h"

#include <algorithm>
#include <iostream>

std::vector<Member*> parents;
std::vector<Member*> generation;
std::vector<Var> result;
std::vector<double> rating;

void createGeneration() {
	int childCount = generationSize / parentsCount;
	for (int i = 0; i < parentsCount; i++) {
		int mCount = membersCount(parents[i]);
		for (int j = 0; j < childCount; j++) {
			std::cout << std::endl << std::endl << "num:" << j << std::endl;
			std::cout << "ptr:" << parents[i] << std::endl;
			std::cout << "size:" << parents[i]->size << std::endl;
			Member* child = duplicate(parents[i]);
			Member* changingMember;
			do {
				int changingMemberNum = rand() % (mCount + 1);
				std::cout << "child: " << child << std::endl;
				changingMember = getMember(child, changingMemberNum);
			} while (changingMember->operation == -1);
			int actionType = int(rand()) % (operations.size() + 2);

			std::cout << "actionType: " << actionType << std::endl;
			switch (actionType) {
			case 0: // add member
				changingMember->members.push_back(new Constant(members[rand() % members.size()]));
				changingMember->size = changingMember->members.size();
				break;

			case 1: {// delete member
				int r = rand() % changingMember->members.size();
				changingMember->members[r]->~Member();
				delete changingMember->members[r];
				changingMember->members.erase(changingMember->members.begin() + r);
				changingMember->size = changingMember->members.size();
				break;
			}
			default:
				changingMember->operation = actionType - 2;
				break;
			}
			generation[i * childCount + j] = child;
		}
	}
}

void performGeneration() {
	result.resize(generation.size());
	rating.resize(generation.size());
	for (int i = 0; i < generation.size(); i++) {
		result[i] = generation[i]->perform();
		rating[i] = result[i].value;
	}
	std::sort(rating.begin(), rating.end());
}

void selection() {
	for (int i = 0; i < parentsCount; i++) {
		parents[i]->~Member();
		delete parents[i];
		for (int j = 0; j < result.size(); j++) {
			if (rating[i] == result[j].value) {
				int k = 0;
				while (result[j].name != generation[k]->perform().name)
					k++;

				parents[i] = new Member(*generation[k]);
			}
		}
	}

	for (int i = 0; i < generationSize; i++) {
		generation[i]->~Member();
		delete generation[i];
	}
}