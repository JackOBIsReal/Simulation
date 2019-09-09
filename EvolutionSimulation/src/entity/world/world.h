#pragma once
#include "core.h"
#include "entity/entity.h"
#include "entity/plant/plant.h"
#include "entity/rabbit/rabbit.h"
#include "entity/fox/fox.h"

namespace sim {
	class world {
	public:
		std::vector<std::pair<plant*,int>> plants;
		std::vector<rabbit*> rabbits;
		std::vector<fox*> foxes;
		std::vector<std::vector<int>> past;

		void addPlant(plant* Plant);

		void addRabbit(rabbit* Rabbit);
		void removeRabbit(rabbit* Rabbit);

		void addFox(fox* Fox);
		void removeFox(fox* Fox);

		void nextDay();

		world(int plantCount, int rabbitCount, int foxCount, int growthRate);

		std::string const toString() const;
		std::string const pastString() const;

		int m_growthRate;
		int days;
	};
}