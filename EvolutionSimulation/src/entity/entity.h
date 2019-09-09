#pragma once

#define STANDART_SPEED 1.0f
#define STANDART_MAX_ENEGRY 1.0f
#define STANDART_SENSITIVITY 1.0f
#define STANDART_ENERGY_PER_MEAL 1.0f
#define STANDART_ENERGY_EFFICIANCE 1.0f

namespace sim {
	enum traits { 
		SPEED = 1, 
		SENSITIVITY, 
		MAX_ENERGY, ENERGY_PER_MEAL, ENERGY_EFFICIENCY
	};

	enum entityType {
		PLANT = 1, RABBIT, FOX
	};

	class world;
	
	class entity {
	public:
		entity();

		virtual void m_moveRandom();
		virtual void m_move(float Direction);

		virtual void m_mutate(std::map<std::string, float> parentValues);

		virtual void m_eat(entity other) {}

		virtual const float m_getValue(traits Trait) const;
		virtual inline const glm::vec2 m_GetPosition() const { return m_position; }
		virtual inline const entityType m_GetType() const { return m_type; }

		virtual const std::string toString() const { return ""; };

	public:
		std::map<traits, float> m_traits;
		glm::vec2 m_position;
		entityType m_type;
		world* m_world;
	};
}