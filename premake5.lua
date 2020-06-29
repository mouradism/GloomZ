workspace "GloomZ"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GloomZ"
	location "GloomZ"
	kind "SharedLib"
	language "c++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}


	filter "system:windows"
		cppdialect "c++17"
		staticruntime "on"
		systemversion "10.0.17763.0"

		defines
		{
			"GL_PLATFORM_WINDOWS",
			"GL_BUILD_DLL",
			"_WINDLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir .. "/Sandbox")
		}

	filter "configurations:Release"
		defines "GL_RELEAS"
		optimize "on"

	filter "configurations:Debug"
		defines "GL_DEBUG"
		symbols "on"

	filter "configurations:Dist"
		defines "GL_DIST"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "c++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"GloomZ/vendor/spdlog/include",
		"GloomZ/src"
	}

	links
	{
		"GloomZ"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "on"
		systemversion "10.0.17763.0"

		defines
		{
			"GL_PLATFORM_WINDOWS"
		}


	filter "configurations:Release"
		defines "GL_RELEAS"
		optimize "on"

	filter "configurations:Debug"
		defines "GL_DEBUG"
		symbols "on"

	filter "configurations:Dist"
		defines "GL_DIST"
		optimize "on"
--[[
	filter { "system:windows", "configurations:Release"}
		buildoptions "/MT"
--]]