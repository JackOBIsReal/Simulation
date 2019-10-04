#pragma once

#define STANDART_SPEED 1.0f
#define STANDART_MAX_ENEGRY 1.0f
#define STANDART_SENSITIVITY 1.0f
#define STANDART_ENERGY_PER_MEAL 1.0f
#define STANDART_ENERGY_EFFICIANCE 1.0f

namespace sim {
	enum traits {
		SPEED,
		SENSITIVITY,
		MAX_ENERGY, ENERGY_PER_MEAL, ENERGY_EFFICIENCY,
		number_of_traits
	};

	enum entityType {
		placeholder_type, PLANT, RABBIT, FOX
	};

	class world;
	
	class entity {
	public:
		//initializes all the common information
		entity(entityType Type = placeholder_type, glm::vec2 Position = glm::vec2(0.0f, 0.0f));

		//moves the entity with it's full speed to a random direction
		virtual void m_moveRandom();
		//moves the entity with it's full speed to a set direction
		virtual void m_move(float Direction);
		//the "intelligenze" of the entity, deciding where to go or 

		//mutates the traits with a standart deviation from the average of the parents traits
		virtual void m_mutate(std::map<std::string, float> Parent1, std::map<std::string, float> Parent2);

		//eats the other entity, has to be different for rabbits and foxes
		virtual void m_eat(entity* other) {}

		//get the value of a given trait, for debugging and analyzation purposes
		virtual const float m_getValue(traits Trait) const;

		//get the current position of the entity
		inline const glm::vec2 m_GetPosition() const { return m_position; }

		//get the type of the entity
		inline const entityType m_GetType() const { return m_type; }

		//returns a string containing the entitys information for deebug purposes
		virtual const std::string toString() const { return ""; };

	public:
		//a map mapping the traits to their values
		std::map<traits, float> m_traits;

		//a vector containing the position of the entity
		glm::vec2 m_position;

		//the enum containing the information about what kind of entity this is
		entityType m_type;
	};
}