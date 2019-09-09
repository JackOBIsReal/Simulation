#include "pch.h"
#include "world.h"

namespace sim{
	void world::addPlant(plant* Plant)
	{
		plants.emplace_back(std::pair<plant*,int>(Plant, 0));
	}
	void world::addRabbit(rabbit* Rabbit)
	{
		rabbits.emplace_back(Rabbit);
	}
	void world::removeRabbit(rabbit* Rabbit)
	{
		std::vector<rabbit*>::iterator it = std::find(rabbits.begin(), rabbits.end(), Rabbit);
		rabbits.erase(it);
		delete Rabbit;
	}
	void world::addFox(fox* Fox)
	{
		foxes.emplace_back(Fox);
	}
	void world::removeFox(fox* Fox)
	{
		std::vector<fox*>::iterator it = std::find(foxes.begin(), foxes.end(), Fox);
		foxes.erase(it);
		delete Fox;
	}
	void world::nextDay()
	{
		int numberOPlants = 0;
		for (int i = 0; i < plants.size(); i++) {
			if (plants[i].second == 0)
				numberOPlants++;
		}
		std::vector<int> lastDay(3);
		lastDay[0] = numberOPlants;
		lastDay[1] = rabbits.size();
		lastDay[2] = foxes.size();
		past.emplace_back(lastDay);

		days++;

		plant::grow(plants);
	}
	world::world(int plantCount, int rabbitCount, int foxCount, int growthRate)
		:m_growthRate(growthRate), days(0)
	{
		for (int i = 0; i < plantCount; i++)
			addPlant(new plant());

		for (int i = 0; i < rabbitCount; i++)
			addRabbit(new rabbit());

		for (int i = 0; i < foxCount; i++)
			addFox(new fox());
	}
	std::string const world::toString() const
	{
		int numberOPlants = 0;
		for (int i = 0; i < plants.size(); i++) {
			if (plants[i].second == 0)
				numberOPlants++;
		}
		std::stringstream ss;
		ss << "Growth: " << m_growthRate << ", plants: " << numberOPlants << ", rabbits: ";
		ss << rabbits.size() << ", foxes: " << foxes.size() << ", day: " << days;
		return ss.str();
	}
	std::string const world::pastString() const
	{
		std::stringstream ss;
		for (int i = 0; i < past.size(); i++) {
			ss << "Day: " << i << ", plants: " << past[i][0] << ", rabbits: " << past[i][1];
			ss << ", foxes: " << past[i][2] << std::endl;
		}
		return ss.str();
	}
}