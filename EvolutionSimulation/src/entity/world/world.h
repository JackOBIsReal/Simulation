#pragma once
#include "core.h"
#include "entity/entity.h"
#include "entity/plant/plant.h"
#include "entity/rabbit/rabbit.h"
#include "entity/fox/fox.h"

namespace sim {
	class world {
	public:
		//the std::vectors containing all currently existing plants, rabbits and foxes
		std::vector<std::pair<plant*,int>> plants;
		std::vector<rabbit*> rabbits;
		std::vector<fox*> foxes;

		//the std::vector containing all the information of all the past days
		std::vector<std::vector<int>> past;

		//adds a plant to the world
		void addPlant(plant* Plant);

		//adds a rabbit to the world
		void addRabbit(rabbit* Rabbit);
		//removes a rabbit from the world (when it was eaten)
		void removeRabbit(rabbit* Rabbit);

		//everything that happened with the rabbit with the fox
		void addFox(fox* Fox);
		void removeFox(fox* Fox);

		//the function getting everything ready for the next day
		void nextDay();

		//initializes the world with the wanted number of plants, rabbits, foxes as well as the information
		//about how many days it takes for a plant to grow back
		world(int plantCount, int rabbitCount, int foxCount, int growthRate);

		//creates a string containing the information about the world for console debugging
		std::string const toString() const;

		//creates a string containing all the information about all the past days
		//for console debugging
		std::string const pastString() const;

		//how many days it takes for a plant to grow back once it has been eaten
		int m_growthRate;

		//the number of days this world has been simulated
		int days;
	};
}