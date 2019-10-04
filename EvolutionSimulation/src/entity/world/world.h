#pragma once
#include "core.h"
#include "entity/entity.h"
#include "entity/plant/plant.h"
#include "entity/rabbit/rabbit.h"
#include "entity/fox/fox.h"

#define LOCK std::lock_guard<std::mutex> lockGuard(interface_lock)

namespace sim {
	class World {
	public:
		//the std::vectors containing all currently existing plants, rabbits and foxes
		std::vector<std::pair<plant*,int>> plants;
		std::vector<rabbit*> rabbits;
		std::vector<fox*> foxes;

		//the std::vector containing all the information of all the past days
		std::vector<int> plantsHistory;
		std::vector<int> rabbitsHistory;
		std::vector<int> foxesHistory;

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
		World(int plantCount, int rabbitCount, int rabbitDay, int foxCount, int foxDay, int growthRate, int doomsday,
			std::array<bool, sim::traits::number_of_traits>& letMutate);

		//creates a string containing the information about the world for console debugging
		std::string const toString();

		//creates a string containing all the information about all the past days
		//for console debugging
		std::string const pastString();

		//how many days it takes for a plant to grow back once it has been eaten
		int m_growthRate;

		//the number of days this world has been simulated
		int days;

		//the day at which the world is terminated automatically
		int m_doomsday;

		int m_rabbitDay;
		int m_foxDay;
		std::array<bool, sim::traits::number_of_traits> m_letMutate;
		bool m_active;

		std::mutex interface_lock;
	};
}