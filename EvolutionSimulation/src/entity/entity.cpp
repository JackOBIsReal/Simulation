#include "pch.h"
#include "core.h"
#include "entity.h"
#include "world/world.h"

#include <glm.hpp>

namespace sim {
	entity::entity()
	{
		m_traits.insert(std::pair<traits, float>(SPEED, STANDART_SPEED));
		m_traits.insert(std::pair<traits, float>(SENSITIVITY, STANDART_SENSITIVITY));
		m_traits.insert(std::pair<traits, float>(MAX_ENERGY, STANDART_MAX_ENEGRY));
		m_traits.insert(std::pair<traits, float>(ENERGY_EFFICIENCY, STANDART_ENERGY_EFFICIANCE));
		m_traits.insert(std::pair<traits, float>(ENERGY_PER_MEAL, STANDART_ENERGY_PER_MEAL));

	}
	void entity::m_moveRandom()
	{
		glm::vec2 movement(m_traits[SPEED], 0);
		//rotate by random float between 0 and 360
		
	}
	void entity::m_move(float Direction)
	{
		glm::vec2 movement(m_traits[SPEED], 0);
		//rotate vector by Direction, Direction is between 0 and 360
	}
	void entity::m_mutate(std::map<std::string, float> parentValues)
	{

	}
	const float entity::m_getValue(traits Trait) const
	{
		return 0.0f;
	}
}