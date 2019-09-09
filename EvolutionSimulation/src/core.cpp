#include "pch.h"
#include "core.h"

namespace sim {
	std::mt19937 randomNumber(0);
	float random()
	{
		return sim::randomNumber() / 4294967295.0f;;
	}
}