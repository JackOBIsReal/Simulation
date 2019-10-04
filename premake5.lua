workspace "EvolutionSimulation"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "EvolutionSimulation"
	location "EvolutionSimulation"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch.h"
	pchsource "EvolutionSimulation/src/pch.cpp"

	

	files
	{
		"%{prj.name}/src/**.h"	,
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"EvolutionSimulation/src/",
		"EvolutionSimulation/vendor/GLM/",
		"../Engine/Engine/src"
	}

	flags
	{
		"MultiProcessorCompile"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		symbols "On"links
		{
			"../Engine/bin/Debug-windows-x86_64/Engine/Engine.lib"
		}

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		optimize "On"links
		{
			"../Engine/bin/Release-windows-x86_64/Engine/Engine.lib"
		}

	filter "configurations:Dist"
		defines "ENGINE_DIST"
		optimize "On"links
		{
			"../Engine/bin/Dist-windows-x86_64/Engine/Engine.lib"
		}
		
IncludeDir = {}