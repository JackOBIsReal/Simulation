#pragma once

class SimLayer : public engine::Layer {
public:
	SimLayer(unsigned int id, int plantCount, int rabbitCount, int rabbitDay, int foxCount, int foxDay, int growthRate, int doomsday,
		std::array<bool, sim::traits::number_of_traits>& letMutate);
	~SimLayer();

	void OnImGuiRender() override;

	void OnUpdate(engine::Timestep ts) override;
public:
	unsigned int m_SimulationID;
	bool m_Running;
	engine::Ref<sim::World> m_World;
	std::string m_mutating;
};

class SimCommandLayer : public engine::Layer {
public:
	SimCommandLayer();
	~SimCommandLayer();

	static engine::Ref<SimCommandLayer> Get() { return s_Instance; }

	void OnImGuiRender() override;

	void OnUpdate(engine::Timestep tx) override;
public:
	std::unordered_map<unsigned int, bool> m_active;
	std::unordered_map<unsigned int, std::vector<std::vector<int>>> m_SimulationResult;
	unsigned int m_currentSimulationIndex = 0;

	static engine::Ref<SimCommandLayer> s_Instance;

	engine::Ref<engine::Layer> m_NewAndHasToBePushed;
};

class SimApp : public engine::Application {
public:
	SimApp();
	~SimApp() {};
};