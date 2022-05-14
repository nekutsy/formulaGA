#include "Global.h"

double mutationCount = 15;
int nowPreset = 0;
double mScore = 0;
std::vector<std::vector<Var>> presets = {
	{//1
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(0, "v"),
		Var(5, "a"),
		Var(10, "t")
	},
	{//2
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(50, "v"),
		Var(1, "a"),
		Var(2, "t")
	},
	{//3
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(-40, "v"),
		Var(5, "a"),
		Var(100, "t")
	},
	{//4
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(1000, "v"),
		Var(200, "a"),
		Var(4, "t")
	},
	{//5
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(-40, "v"),
		Var(0, "a"),
		Var(500, "t")
	},
	{//6
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(2, "v"),
		Var(8, "a"),
		Var(1, "t")
	},
	{//7
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(950, "v"),
		Var(-20, "a"),
		Var(5, "t")
	},
	{//8
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(-700, "v"),
		Var(-3, "a"),
		Var(10, "t")
	},
	{//9
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(10, "v"),
		Var(5, "a"),
		Var(-3, "t")
	},
	{//10
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(-38, "v"),
		Var(0, "a"),
		Var(0, "t")
	},
};
std::vector<Var>& members = presets[0];

extern std::array<double, presetsCount> expectedResults = {
	50, 52, 460, 1800, -40, 10, 850, -730, -5, -38
};

std::array<Member*, parentsCount> parents;
std::array<Member*, generationSize> generation;