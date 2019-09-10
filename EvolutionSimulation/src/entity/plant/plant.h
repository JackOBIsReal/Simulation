#pragma once

namespace sim {
	class plant : public entity {
	public:
		//grows every plant in the fiven vector
		//positioned here to make it more logically
		static void grow(std::vector<std::pair<plant*,int>>& plants);
		
		//initializes the plant in the given location
		//random location if none is given
		plant(glm::vec2 Position = glm::vec2(random() * 100.0f, random() * 100.0f));

		//position the plant randomly and make it edible
		void m_recycle();

		//create a string with the information of the plant for console debugging
		virtual const std::string toString() const;
	public:
		//a boolean holding the information weather the plant is edible or not
		bool m_eaten;
	};
}