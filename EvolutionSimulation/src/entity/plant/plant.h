#pragma once

namespace sim {
	class plant : public entity {
	public:
		static void grow(std::vector<std::pair<plant*,int>>& plants);
		plant(glm::vec2 position);
		plant();
		~plant();

		virtual void m_moveRandom() override;
		virtual void m_move(float Direction) override {}

		virtual void m_eat(entity other) override {}

		virtual const float m_getValue(traits Trait) const override { return 0.0f; };

		virtual const std::string toString() const;
	public:
		bool m_eaten;
	};
}