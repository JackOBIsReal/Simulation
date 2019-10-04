#pragma once
#include "entity/entity.h"

namespace sim {
	class fox : public entity {
	public:
		//initializes the fox with every needed variable
		fox(glm::vec2 Position = glm::vec2(engine::random() * 100.0f, engine::random() * 100.0f));

		//the function teaching the fox how to eat
		virtual void m_eat(entity* other) override;
	};
}