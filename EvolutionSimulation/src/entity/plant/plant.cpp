#include "pch.h"
#include "core.h"
#include "entity/entity.h"
#include "plant.h"
#include "entity/world/world.h"
#include <math.h>

namespace sim {
	void plant::grow(std::vector<std::pair<plant*,int>>& plants)
	{
		std::vector<int> toRemove(0);
		for (int i = 0; i < plants.size(); i++) {
			if (plants[i].second == 0)
				plants[i].first->m_moveRandom();
			else
				plants[i].second -= 1;
		}
	}
	plant::plant(glm::vec2 Position)
	{
		m_position = Position;
		m_type = PLANT;
		m_eaten = false;
	}
	plant::plant()
	{
		m_position = glm::vec2(random() * 100.0f, random() * 100.0f);
		m_type = PLANT;
		m_eaten = false;
	}
	plant::~plant()
	{
	}
	void plant::m_moveRandom()
	{
		m_eaten = false;
		m_position = glm::vec2(random() * 100.0f, random() * 100.0f);
	}
	const std::string plant::toString() const
	{
		std::stringstream ss;
		ss << "X: " << m_position.x << ", y: " << m_position.y << ", eaten: ";
		if (m_eaten)
			ss << "true";
		else
			ss << "false";

		return ss.str();
	}
}