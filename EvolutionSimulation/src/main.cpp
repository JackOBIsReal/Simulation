#include "pch.h"
#include "core.h"
#include "entity/world/world.h"

int main() {
	std::time_t result = std::time(nullptr);
	sim::randomNumber.seed((long long)std::localtime(&result));
	
	for (unsigned long long newseed = 1; newseed < 18446744073709551614 / std::pow(sim::randomNumber(), 1.0f / 10.0f);) {
		newseed *= (std::pow(sim::randomNumber(), 1.0f / 10.0f) + (long long)std::localtime(&result)) / 2;
		sim::randomNumber.seed(newseed);
	}
	
	sim::world* mainWorld = new sim::world(200, 50, 0, 10);
}