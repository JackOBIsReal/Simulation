#pragma once

namespace engine {
	//mersenne twister engine for randomization
	extern std::mt19937 randomNumber;

	//function for a random scalar between 1.0f and 0.0f
	float random();
}