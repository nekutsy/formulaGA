#include "Global.h"

double mutationCount = 15;
int nowPreset = 0;
double mScore = 0;
std::vector<std::vector<Var>> presets = {
	{//1
		Var(2, "2"),
		Var(0.5, "0.5"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(0, "v0"),
		Var(10, "a"),
		Var(3, "t")
	},
	{//2
		Var(2, "2"),
		Var(0.5, "0.5"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(100, "v0"),
		Var(1, "a"),
		Var(2, "t")
	},
	{//3
		Var(2, "2"),
		Var(0.5, "0.5"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(25, "v0"),
		Var(0, "a"),
		Var(4, "t")
	},
	{//4
		Var(2, "2"),
		Var(0.5, "0.5"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(-900, "v0"),
		Var(1, "a"),
		Var(30, "t")
	},
	{//5
		Var(2, "2"),
		Var(0.5, "0.5"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(20, "v0"),
		Var(5, "a"),
		Var(10, "t")
	},
	{//6
		Var(2, "2"),
		Var(0.5, "0.5"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(40, "v0"),
		Var(8, "a"),
		Var(0, "t")
	},
	{//7
		Var(2, "2"),
		Var(0.5, "0.5"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(4, "v0"),
		Var(30, "a"),
		Var(5, "t")
	},
	{//8
		Var(2, "2"),
		Var(0.5, "0.5"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(1, "v0"),
		Var(100, "a"),
		Var(10, "t")
	},
	{//9
		Var(2, "2"),
		Var(0.5, "0.5"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(5, "v0"),
		Var(8, "a"),
		Var(2, "t")
	},
	{//10
		Var(2, "2"),
		Var(0.5, "0.5"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(325, "v0"),
		Var(0, "a"),
		Var(4, "t")
	},
	{//11
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(-100, "v0"),
		Var(10, "a"),
		Var(2, "t")
		},
	{//12
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(4, "v0"),
		Var(-1, "a"),
		Var(5, "t")
	},
	{//13
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(10, "v0"),
		Var(13, "a"),
		Var(1, "t")
	},
	{//14
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(8, "v0"),
		Var(2, "a"),
		Var(5, "t")
	},
	{//15
		Var(2, "2"),
		Var(10, "10"),
		Var(1, "1"),
		Var(-1, "-1"),

		Var(20, "v0"),
		Var(10, "a"),
		Var(6, "t")
	},
};
std::vector<Var>& members = presets[0];

extern std::array<double, presetsCount> expectedResults = {
	90, 204, 100, -26100, 700, 0, 770, 10010, 42, 1300, -160, -5, 23, 90, 480
};

std::array<Member*, parentsCount> parents;
std::array<Member*, generationSize> generation;