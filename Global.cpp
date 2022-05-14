#include "Global.h"

float mutationCount = 15;
int nowPreset = 0;
float mScore = 0;
std::vector<std::vector<Var>> presets = {
	{
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(0, "v0"),
		Var(5, "t"),
		Var(10, "a")
	},
	{
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(4, "v0"),
		Var(20, "t"),
		Var(1, "a")
	},
	{
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(-10, "v0"),
		Var(2, "t"),
		Var(2, "a")
	},
	{
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(30, "v0"),
		Var(-2, "t"),
		Var(15, "a")
	},
};
std::vector<Var>& members = presets[0];

extern std::array<double, presetsCount> expectedResults = {
	250, 400, -12, 0
};

std::array<Member*, parentsCount> parents;
std::array<Member*, generationSize> generation;