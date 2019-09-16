#pragma once
#include "entity/entity.h"

namespace sim {
	class rabbit : public entity {
	public:
		//eats a provided plant
		virtual void m_eat(entity* other) override;
	};
}