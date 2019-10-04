#include "pch.h"
#include "core.h"
#include "entity/entity.h"
#include "plant.h"
#include "entity/world/world.h"
#include <math.h>

namespace sim {
	void plant::grow(std::vector<std::pair<plant*,int>>& plants)
	{
		//iteratin through the plants
		for (int i = 0; i < plants.size(); i++) {
			if (plants[i].second == 0)
				//the fully grown plants are positioned randomly and ready to be eaten
				plants[i].first->m_moveRandom();
			else
				//the plants grow by one round
				plants[i].second -= 1;
		}
	}
	plant::plant(glm::vec2 Position) :entity(PLANT, Position)
	{
		//innitialize the plant with every variable, including the parent constructor
		m_position = Position;
		m_type = PLANT;
		m_eaten = false;
	}
	void plant::m_recycle()
	{
		//moves the Plant to a random position and makes it eatable
		m_position = glm::vec2(engine::random() * 100.0f, engine::random() * 100.0f);
		m_eaten = false;
	}
	const std::string plant::toString() const
	{
		//creates a string with the information of the plant for console debugging
		std::stringstream ss;
		ss << "X: " << m_position.x << ", y: " << m_position.y << ", eaten: ";
		if (m_eaten)
			ss << "true";
		else
			ss << "false";

		return ss.str();
	}
}