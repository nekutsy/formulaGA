#include "UseCSV.h"

#include <iostream>
#include <fstream>

#include "UseFunctions.h"

std::string desiredValueName;
std::vector<int> ignoredValues = { };
std::vector<int> dateValues = {  };

void c_createPreset() {
	ignoredValues.push_back(desiredValueNum);
	std::sort(ignoredValues.begin(), ignoredValues.end());

	std::string fileName;
	std::cout << "fileName: ";
	std::cin >> fileName;
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		std::cout << "file can't be open";
		abort();
	}

	varNames = c_parseToStr(file);
	desiredValueName = varNames[desiredValueNum];
	c_deleteIgnoredValues(varNames);
	varCount = varNames.size();
	
	for (int i = 0; i < maxLinesCount && file.eof() == 0; i++) {
		std::vector<std::string> line = c_parseToStr(file);
		if (line[0] == "")
			break;
		expectedResults.push_back(std::stof(line[desiredValueNum]));
		c_deleteIgnoredValues(line);

		std::vector<float> values;
		values.resize(line.size());
		for (int j = 0; j < line.size(); j++)
			if (std::find(dateValues.begin(), dateValues.end(), j) != dateValues.end())
				values[j] = c_dateToFloat(line[j]);
			else
				values[j] = std::stof(line[j]);
		presets.push_back(values);
	}
	presetsCount = presets.size();
	unevenMultiplier = 0;
}

std::vector<std::string> c_parseToStr(std::ifstream& f) {
	std::vector<std::string> out = {""};
	char ch = f.get();
	int i = 0;
	while (ch != 10 && f.eof() == 0) {
		if (ch == ',')
			out.push_back("");
		else
			out.back().push_back(ch);
		ch = f.get();
		i += 1;
	}
	return out;
}

float c_dateToFloat(std::string& str) {
	float day = NAN, month = NAN, year = NAN;
	int x1 = 0, x2 = 0;
	for (; std::isdigit(str[x2]) && x2 < str.size(); x2++);
	day = std::stoi(str.substr(x1, x2 - x1));
	for (x2 += 1, x1 = x2; x2 < str.size() && std::isdigit(str[x2]); x2++);
	month = std::stoi(str.substr(x1, x2 - x1));
	for (x2 += 1, x1 = x2; x2 < str.size() && std::isdigit(str[x2]); x2++);
	year = std::stoi(str.substr(x1, x2 - x1));
	if ((day == 9999 && month == 99 && year == 99) || x2 != str.size())
		return NAN;
	return day + month * 30.436849898 + year * 365.24219878 - referenceDate;
}

void c_regulator(bool detail) {
	f_regulator(detail);
	unevenMultiplier = 0;
}

void c_display(int num, int width, int height){
	Member* e = parents[num];
	std::cout << "testCount (-1 for manual enter): ";
	int testCount;
	std::cin >> testCount;
	std::cout << e->getName() << ":" << std::endl << std::endl;
	
	if (testCount == -1) {
		std::vector<float> vec;
		vec.resize(varCount);
		for (int i = 0; i < varCount; i++) {
			std::cout << varNames[i] << ": ";
			std::cin >> vec[i];
		}
		std::cout << desiredValueName << " = " << e->perform(vec) << std::endl;
		return;
	}

	for (int i = 0; i < testCount; i++) {
		int testNum = rand() % presetsCount;
		std::cout << "presetNum: " << testNum << std::endl;
		for (int j = 0; j < varCount - 1; j++)
			std::cout << varNames[j] << " = " << presets[testNum][j] << ", ";
		std::cout << varNames.back() << " = " << presets[testNum].back() << std::endl;
		std::cout << desiredValueName << " = " << e->perform(presets[testNum]) << " (" << expectedResults[testNum] << ")" << std::endl << std::endl;
	}
}

void c_displayInfo(Expression* e, bool detail) {
	std::cout << desiredValueName << " = " << e->getName() << std::endl;
	if (detail) {
		std::cout << "fitness: " << e->fitn << std::endl;
		std::cout << "size: " << e->size << std::endl;
	}
}