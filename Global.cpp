#include "Global.h"

double mutationCount = 15;
int nowPreset = 0;
double mScore = 5;
std::vector<std::vector<Var>> presets = {
	{
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(-2, "x"),
	Var(-2, "y"),
	Var(2, "Fx"),
	Var(2, "Fy"),
}, {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(1, "x"),
	Var(-2, "y"),
	Var(-3, "Fx"),
	Var(2, "Fy"),
}, {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(-1, "x"),
	Var(-3, "y"),
	Var(1.25, "Fx"),
	Var(2.5, "Fy"),
}, {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(2, "x"),
	Var(-1.25, "y"),
	Var(-3, "Fx"),
	Var(0.5, "Fy"),
}, {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(3, "x"),
	Var(-3, "y"),
	Var(-3.5, "Fx"),
	Var(3.5, "Fy"),
}, {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(5, "x"),
	Var(2, "y"),
	Var(-6, "Fx"),
	Var(-3, "Fy"),
}, {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(1.25, "x"),
	Var(2, "y"),
	Var(-0.75, "Fx"),
	Var(-3, "Fy"),
}, {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(0, "x"),
	Var(1.25, "y"),
	Var(1.5, "Fx"),
	Var(-0.75, "Fy"),
}, {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(0.5, "x"),
	Var(1.5, "y"),
	Var(-3, "Fx"),
	Var(-3, "Fy"),
}, {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(-2, "x"),
	Var(1.5, "y"),
	Var(3, "Fx"),
	Var(-1, "Fy"),
}, {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(-3.5, "x"),
	Var(3.5, "y"),
	Var(3, "Fx"),
	Var(-3, "Fy"),
}, {
	Var(1, "1"),
	Var(-1, "-1"),
	Var(2, "2"),
	
	

	Var(-2, "x"),
	Var(-2, "y"),
	Var(1.25, "Fx"),
	Var(2.5, "Fy"),
},
};
std::vector<Var>& members = presets[0];

extern std::array<double, presetsCount> expectedResults = {
	-1, -0.5, 0, 0.5, 1, 1, 1, 0.5, 0, -0.5, -1, -1
};

std::array<Member*, parentsCount> parents;
std::array<Member*, generationSize> generation;