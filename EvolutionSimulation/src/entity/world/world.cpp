#include "pch.h"
#include "world.h"

namespace sim{
	//adds a plant to the world
	void world::addPlant(plant* Plant)
	{
		//emplaces a pair of the plant and an int. The int is used lateron while the plant is growing
		plants.emplace_back(std::pair<plant*,int>(Plant, 0));
	}

	//adds a rabbit to the world
	void world::addRabbit(rabbit* Rabbit)
	{
		//emplaces the rabbit into the rabbits std::vector
		rabbits.emplace_back(Rabbit);
	}

	//removes a rabbit from the world (when it was eaten)
	void world::removeRabbit(rabbit* Rabbit)
	{
		//find the rabbit in the rabbits std::vector
		std::vector<rabbit*>::iterator it = std::find(rabbits.begin(), rabbits.end(), Rabbit);
		//removes the rabbit from the std::vector
		rabbits.erase(it);
		//deletes the rabbit to which the pointer was pointing in order to prevent memory overflow
		delete Rabbit;
	}
	//everything that happened with the rabbit with the fox
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

	//the function getting everything ready for the next day
	void world::nextDay()
	{
		//calculates the number of edible plants by iterating every plant and counting them
		int numberOPlants = 0;
		for (int i = 0; i < plants.size(); i++) {
			if (plants[i].second == 0)
				numberOPlants++;
		}
		//creates a std::vector holding integers containing the information about the last day
		std::vector<int> lastDay(3);
		lastDay[0] = numberOPlants;
		lastDay[1] = rabbits.size();
		lastDay[2] = foxes.size();
		//adds the last day into the std::vector containing the information about every last day
		past.emplace_back(lastDay);

		//increments the daycounter
		days++;

		//grows every plant in the world if not fully grown
		plant::grow(plants);
	}

	//initializes the world with the wanted number of plants, rabbits, foxes as well as the information
	//about how many days it takes for a plant to grow back
	world::world(int plantCount, int rabbitCount, int foxCount, int growthRate)
		:m_growthRate(growthRate), days(0)
	{
		//creates the plants
		for (int i = 0; i < plantCount; i++)
			addPlant(new plant());

		//creates the rabbits
		for (int i = 0; i < rabbitCount; i++)
			addRabbit(new rabbit());

		//creates the foxes
		for (int i = 0; i < foxCount; i++)
			addFox(new fox());
	}

	//creates a string containing the information about the world for console debugging
	std::string const world::toString() const
	{
		//counts the number of edible plants
		int numberOPlants = 0;
		for (int i = 0; i < plants.size(); i++) {
			if (plants[i].second == 0)
				numberOPlants++;
		}

		//creates a stringstream, adds the information and returns the string
		std::stringstream ss;
		ss << "Growth: " << m_growthRate << ", plants: " << numberOPlants << ", rabbits: ";
		ss << rabbits.size() << ", foxes: " << foxes.size() << ", day: " << days;
		return ss.str();
	}

	//creates a string containing all the information about all the past days
	//for console debugging
	std::string const world::pastString() const
	{
		//creates the stringstream, iterates over the std::vector containing the information 
		//of every last day and then creates a line for it in the output stringstream
		std::stringstream ss;
		for (int i = 0; i < past.size(); i++) {
			ss << "Day: " << i << ", plants: " << past[i][0] << ", rabbits: " << past[i][1];
			ss << ", foxes: " << past[i][2] << std::endl;
		}
		//returns the stringstream's string
		return ss.str();
	}
}