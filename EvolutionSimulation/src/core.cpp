#include "pch.h"
#include "core.h"

namespace sim {
}
namespace engine {
	//mersenne twister engine for randomization
	std::mt19937 randomNumber(0);

	//function for a random float between 1.0f and 0.0f
	float random()
	{
		//the mt19937 algorithm creates a random number between 0 and 4294967295,
		//this number is then divided by the maximum number in order to have a scalar
		return engine::randomNumber() / 4294967295.0f;
	}
}