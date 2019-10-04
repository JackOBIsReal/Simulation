#include "pch.h"
#include "world.h"

namespace sim{
	//adds a plant to the world
	void World::addPlant(plant* Plant)
	{
		//emplaces a pair of the plant and an int. The int is used lateron while the plant is growing
		LOCK;
		plants.emplace_back(std::pair<plant*,int>(Plant, 0));
	}

	//adds a rabbit to the world
	void World::addRabbit(rabbit* Rabbit)
	{
		//emplaces the rabbit into the rabbits std::vector
		LOCK;
		rabbits.emplace_back(Rabbit);
	}

	//removes a rabbit from the world (when it was eaten)
	void World::removeRabbit(rabbit* Rabbit)
	{
		LOCK;
		//find the rabbit in the rabbits std::vector
		std::vector<rabbit*>::iterator it = std::find(rabbits.begin(), rabbits.end(), Rabbit);
		//removes the rabbit from the std::vector
		rabbits.erase(it);
		//deletes the rabbit to which the pointer was pointing in order to prevent memory overflow
		delete Rabbit;
	}
	//everything that happened with the rabbit with the fox
	void World::addFox(fox* Fox)
	{
		LOCK;
		foxes.emplace_back(Fox);
	}
	void World::removeFox(fox* Fox)
	{
		LOCK;
		std::vector<fox*>::iterator it = std::find(foxes.begin(), foxes.end(), Fox);
		foxes.erase(it);
		delete Fox;
	}

	//the function getting everything ready for the next day
	void World::nextDay()
	{
		//calculates the number of edible plants by iterating every plant and counting them
		{
			LOCK;
			int numberOPlants = 0;
			for (int i = 0; i < plants.size(); i++) {
				if (plants[i].second == 0)
					numberOPlants++;
			}
			//creates a std::vector holding integers containing the information about the last day
			plantsHistory.emplace_back(numberOPlants);
			rabbitsHistory.emplace_back(rabbits.size());
			foxesHistory.emplace_back(foxes.size());
		}

		//increments the daycounter
		days++;

		//grows every plant in the world if not fully grown
		plant::grow(plants);
	}

	//initializes the world with the wanted number of plants, rabbits, foxes as well as the information
	//about how many days it takes for a plant to grow back
	World::World(int plantCount, int rabbitCount, int rabbitDay, int foxCount, int foxDay, int growthRate, int doomsday,
		std::array<bool, sim::traits::number_of_traits>& letMutate)
		:m_growthRate(growthRate), days(0), m_doomsday(doomsday), m_foxDay(foxDay), m_rabbitDay(rabbitDay),
		m_letMutate(letMutate), m_active(false)
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

	//creates a string containing the information about the World for console debugging
	std::string const World::toString()
	{
		//counts the number of edible plants
		LOCK;
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
	std::string const World::pastString()
	{
		//creates the stringstream, iterates over the std::vector containing the information 
		//of every last day and then creates a line for it in the output stringstream
		std::stringstream ss;
		LOCK;
		for (int i = 0; i < rabbitsHistory.size(); i++) {
			ss << "Day: " << i << ", rabbits: " << rabbitsHistory[i];
			ss << ", foxes: " << foxesHistory[i] << std::endl;
		}
		//returns the stringstream's string
		return ss.str();
	}
}