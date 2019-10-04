#include "pch.h"
#include "core.h"
#include "entity.h"
#include "world/world.h"

namespace sim {
	//initializes all the common information
	entity::entity(entityType Type, glm::vec2 Position)
	{
		//initializes the traits to the standart values
		m_traits.insert(std::pair<traits, float>(SPEED, STANDART_SPEED));
		m_traits.insert(std::pair<traits, float>(SENSITIVITY, STANDART_SENSITIVITY));
		m_traits.insert(std::pair<traits, float>(MAX_ENERGY, STANDART_MAX_ENEGRY));
		m_traits.insert(std::pair<traits, float>(ENERGY_EFFICIENCY, STANDART_ENERGY_EFFICIANCE));
		m_traits.insert(std::pair<traits, float>(ENERGY_PER_MEAL, STANDART_ENERGY_PER_MEAL));

		//initiates the entity in a given Position
		m_position = Position;

		//initializes the type with the given type
		m_type = Type;
	}

	//moves the entity with it's full speed to a random direction
	void entity::m_moveRandom()
	{
		//creates a vector with the entity's speed als length and then
		//rotates it by a random angle
		glm::vec2 movement(m_traits[SPEED], 0);

		glm::rotate(movement, engine::random() * 360);

		m_position += movement;

		//makes shure that the entity stays inside the world
		if (m_position.x > 100.0f)
			m_position.x = 100.0f;
		if (m_position.y > 100.0f)
			m_position.y = 100.0f;
	}

	//moves the entity with it's full speed to a set direction
	void entity::m_move(float Direction)
	{
		//creates a vector with the entity's speed as length and then
		//rotates it by a set angle
		glm::vec2 movement(m_traits[SPEED], 0);

		glm::rotate(movement, Direction * 360);

		m_position += movement;

		//makes shure that the entity stays inside the world
		if (m_position.x > 100.0f)
			m_position.x = 100.0f;
		if (m_position.y > 100.0f)
			m_position.y = 100.0f;
	}

	//mutates the traits with a standart deviation from the average of the parents traits
	void entity::m_mutate(std::map<std::string, float> Parent1, std::map<std::string, float> Parent2)
	{

	}

	//get the value of a given trait, for debugging and analyzation purposes
	const float entity::m_getValue(traits Trait) const
	{
		return 0.0f;
	}
}