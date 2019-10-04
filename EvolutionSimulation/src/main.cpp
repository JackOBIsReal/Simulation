#include "pch.h"
#include "core.h"

#include "imgui.h"
#include "entity/world/world.h"

#include "Engine.h"
#include "main.h"

//	
//	
//	
//	
//	
//	
//	

engine::Application* engine::createApplication() {
	return new SimApp();
}

using namespace sim;



SimLayer::SimLayer(unsigned int id, int plantCount, int rabbitCount, int rabbitDay, int foxCount, int foxDay, int growthRate,
	int doomsday, std::array<bool, sim::traits::number_of_traits>& letMutate)
	: Layer("Simulation##" + std::to_string(id)), m_SimulationID(id), m_Running(false)
{
	std::string mutating;
	if (letMutate[SPEED])
		mutating += ", speed";
	if (letMutate[SENSITIVITY])
		mutating += ", sensitivity";
	if (letMutate[MAX_ENERGY])
		mutating += ", maximum energy";
	if (letMutate[ENERGY_EFFICIENCY])
		mutating += ", energy efficiancy";
	if (letMutate[ENERGY_PER_MEAL])
		mutating += ", energy per meal";
	m_mutating = mutating.substr(2, mutating.size());
	m_World = engine::Ref<World>(new World(plantCount, rabbitCount, rabbitDay, foxCount, foxDay, growthRate, doomsday, letMutate));
}

SimLayer::~SimLayer()
{
}

void SimLayer::OnImGuiRender()
{
	ImGui::Begin(("Simulation##" + std::to_string(m_SimulationID)).c_str());
	ImGui::SetWindowSize(ImVec2(std::round(400.0f * 3.0f / 2.0f), 400.0f) , ImGuiCond_Once);
	int numberOPlants = 0;
	//an own scope for threadsaveness
	{
		std::lock_guard<std::mutex> lockGuard(m_World->interface_lock);
		for (auto plant :m_World->plants) {
			if (plant.second == 0)
				numberOPlants++;
		}
		ImGui::Text(("Number of plants: " + std::to_string(numberOPlants)).c_str());
		ImGui::Text(("Number of rabbits: " + std::to_string(m_World->rabbits.size())).c_str());
		ImGui::PlotLines("##0", (float*)m_World->rabbitsHistory.data(), m_World->rabbitsHistory.size());
		ImGui::Text(("Number of foxes: " + std::to_string(m_World->foxes.size())).c_str());
		ImGui::PlotLines("##1", (float*)m_World->foxesHistory.data(), m_World->foxesHistory.size());
	}
	ImGui::Text("The traits that are being mutated are:");
	ImGui::Text(m_mutating.c_str());
	if(m_Running){
		if (ImGui::Button("Stop this simulation")) {
			m_Running = false;
			m_World->m_active = false;
		}
	}
	else {
		if (ImGui::Button("Start this simulation")) {
			m_Running = true;
			m_World->m_active = true;
		}
	}
	ImGui::End();
}

void SimLayer::OnUpdate(engine::Timestep ts)
{
}

SimApp::SimApp()
	:Application()
{
	Application::Get().PushLayer(engine::Ref<engine::Layer>(new SimCommandLayer()));
}
SimCommandLayer::SimCommandLayer()
	: Layer("Command")
{
	std::time_t result = std::time(nullptr);
	engine::randomNumber.seed((long long)std::localtime(&result));

	for (unsigned long long newseed = 1; newseed < 18446744073709551614 / std::pow(engine::randomNumber(), 1.0f / 10.0f);) {
		newseed *= (std::pow(engine::randomNumber(), 1.0f / 10.0f) + (long long)std::localtime(&result)) / 2;
		engine::randomNumber.seed(newseed);
	}
}
SimCommandLayer::~SimCommandLayer()
{
}

void SimCommandLayer::OnImGuiRender()
{
	static bool newSimulationPopupWindow = false;
	static std::vector;
	static float test = 0.0f;
	ImGui::Begin("Control panel");
	ImGui::SetWindowSize(ImVec2(350.0f, std::round(350.0f*3.0f/2.0f)), ImGuiCond_Once);
	if (ImGui::Button("Create new simulation"))
		newSimulationPopupWindow = true;


	if(newSimulationPopupWindow) {
		static int plants = 200;
		static int rabbits = 50;
		static int rabbitDay = 0;
		static int foxes = 50;
		static int foxDay = 5;
		static int growthrate = 1;
		static int doomsDay = 0;
		static std::array<bool, number_of_traits> mutates;
		static bool mutates_is_initialized = false;
		if (!mutates_is_initialized) {
			mutates_is_initialized = true;

			for (auto& value : mutates) {
				value = true;
			}
		}
		ImGui::SetNextWindowSize(ImVec2(850.0f, 500.0f), ImGuiCond_Once);
		ImGui::Begin("Create new simulation");
		ImGui::Text("Please note that putting big numbers into the following input fields will slow down the simulation exponentially.");
		ImGui::Text("Number of days it takes a plant to regrow");
		ImGui::InputInt("##0", &growthrate);
		ImGui::Text("Number of plants in this simulation");
		ImGui::InputInt("##1", &plants);
		ImGui::Text("Number of rabbits in this simulation");
		ImGui::InputInt("##2", &rabbits);
		ImGui::Text("The day on which the rabbits will start appearing");
		ImGui::InputInt("##3", &rabbitDay);
		ImGui::Text("Number of foxes in this simulation");
		ImGui::InputInt("##4", &foxes);
		ImGui::Text("The Day on which the foxes will start appearing");
		ImGui::InputInt("##5", &foxDay);
		ImGui::Text("The day on which the simulation is going to stop automatically.");
		ImGui::Text("Set to zero to let it run indefinetely, in this case you have to stop it manually.");
		ImGui::InputInt("##6", &doomsDay);
		ImGui::Text("The following checkboxes will decide weather or not the given traits are being mutated in this simulation.");
		ImGui::Checkbox("Speed", &mutates[SPEED]);
		ImGui::Checkbox("Sensitivity", &mutates[SENSITIVITY]);
		ImGui::Checkbox("The maximum energy of the animal", &mutates[MAX_ENERGY]);
		ImGui::Checkbox("The energy efficiancy of the animal (how much a step costs)", &mutates[ENERGY_EFFICIENCY]);
		ImGui::Checkbox("The amount of energy the animal gets from eating", &mutates[ENERGY_PER_MEAL]);
		if (ImGui::Button("Create")) {
			engine::Application::Get().PushLayer(engine::Ref<engine::Layer>(new SimLayer(
			m_currentSimulationIndex, plants, rabbits, rabbitDay, foxes, foxDay, growthrate, doomsDay, mutates)));
			m_currentSimulationIndex++;
			newSimulationPopupWindow = false;
		}
		ImGui::End();
	}
	ImGui::End();
}

void SimCommandLayer::OnUpdate(engine::Timestep tx)
{
	if (engine::Input::KeyPressed(engine::key.escape) || engine::Input::KeyPressed(engine::key.del))
		engine::Application::Get().Terminate();
}
