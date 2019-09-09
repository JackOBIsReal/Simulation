#pragma once
#include "entity/entity.h"

namespace sim {
	class fox : public entity {
		virtual void m_eat(entity other) override;
	};
}