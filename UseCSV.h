#pragma once

#include <algorithm>

#include "Equation.h"
#include "Global.h"
#include "BaseGA.h"

const int maxLinesCount = 100000;
const int desiredValueNum = 0;
const float referenceDate = 2000 * 365.24219878;

extern std::string desiredValueName;
extern std::vector<int> ignoredValues;
extern std::vector<int> dateValues;

void c_createPreset();
std::vector<std::string> c_parseToStr(std::ifstream& f);
float c_dateToFloat(std::string& str);

template<typename Type>
std::vector<Type> deleteIgnoredValues(std::vector<Type>& vec);

void c_regulator(bool detail);
void c_display(int num, int width = 237, int height = 60);
void c_displayInfo(Expression* e, bool detail = false);

template<typename Type>
inline std::vector<Type> c_deleteIgnoredValues(std::vector<Type>& vec) {
	for (int i = ignoredValues.size() - 1; i >= 0; i--)
		vec.erase(vec.begin() + ignoredValues[i]);
	return vec;
}
