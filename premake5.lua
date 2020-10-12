workspace "Shushao"
	architecture "x64"
    startproject "Game"

	configurations {
		"Debug",
		"Release",
		"Dist"
    }

    --[[ rebuildcommands {
        "make %{cfg.buildcfg} rebuild"
    } ]]

    --outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    outputdir = "%{cfg.buildcfg}"
    Game = "Game"
    Engine = "Shushao"
    gamebin = "../bin/" .. outputdir .. "/%{Game}/"
    enginebin = "../bin/" .. outputdir .. "/%{Engine}/"

    include "Shushao/vendor/Box2D.lua"
    include "Shushao/vendor/boost.lua"
    include "Shushao/vendor/freetype.lua"
    include "Shushao/vendor/Glad.lua"
    include "Shushao/vendor/GLFW.lua"
    include "Shushao/vendor/imgui.lua"
    include "Shushao/vendor/SOIL.lua"
    include "Shushao/vendor/spdlog.lua"

project "Shushao"
	location "Shushao"
	kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    targetname "libshushao"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "sepch.h"
    pchsource "%{Engine}/src/sepch.cpp"

    files {
		"%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
	}

    includedirs {
        "%{prj.name}/src",
		"%{Engine}/vendor/GLFW/include",
		"%{Engine}/vendor/Glad/include",
		"%{Engine}/vendor/SOIL/include",
        "%{Engine}/vendor/spdlog/include",
		"%{Engine}/vendor/freetype/include",
		"%{Engine}/vendor/glm",
		"%{Engine}/vendor/boost",
		"%{Engine}/vendor/Box2D"
    }

	filter "system:windows"
        systemversion "latest"

        defines {
            "SE_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter { "configurations:Release", "toolset:gcc" }
        buildoptions { "-O2", "-std=c++17" }
        linkoptions { "-s -mwindows"}

    filter { "configurations:Debug", "toolset:gcc" }
        buildoptions { "-std=c++17", "-Wall", "-fmax-errors=4", "-Wfatal-errors" }

    configuration "Debug"
		defines "SE_DEBUG"
		runtime "Debug"
		symbols "On"
        buildoptions "/MTd"

    configuration "Release"
		defines "SE_RELEASE"
		runtime "Release"
		optimize "On"
        buildoptions "/MT"

    configuration "Dist"
		defines "SE_DIST"
		runtime "Release"
		optimize "On"
        buildoptions "/MT"


project "Shushao Resources"
    location "Shushao"
    kind "SharedLib"
    targetname "shushaores"
    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/Shushao")
    objdir ("obj/" .. outputdir .. "/Shushao")

    files {
        "Shushao/src/Shushao/Resources/**.h",
        "Shushao/src/Shushao/Resources/**.rc"
    }

    postbuildcommands {
        ("{COPY} %{enginebin}/*.dll %{gamebin}")
    }

    linkoptions "/NOENTRY"

    configuration "Debug"
        buildoptions "/MDd"

    configuration "Release"
        buildoptions "/MD"

project "Game"
	location "Game"
	kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    debugdir ("bin/" .. outputdir .. "/%{prj.name}")
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.rc",
	}

	includedirs {
        "%{Engine}/src",
		"%{Engine}/vendor/glm",
        "%{Engine}/vendor/spdlog/include",
		"%{Engine}/vendor/freetype/include",
		"%{Engine}/vendor/SOIL/include",
		"%{Engine}/vendor/boost"
    }

    libdirs {
		"%{Engine}/vendor/Box2D/lib",
		"%{Engine}/vendor/freetype/objs",
		"%{Engine}/vendor/SOIL/lib",
		"%{Engine}/vendor/GLFW/lib",
		"%{Engine}/vendor/Glad/lib",
		"%{Engine}/vendor/spdlog/lib",
        "%{Engine}/vendor/boost/stage/lib"
    }

    links {
        Engine,
        "GLFW",
        "Glad",
        "SOIL2",
        "Box2D",
        "freetype",
        "spdlog",
        "opengl32",
        "libboost_context-vc142-mt-sgd-x64-1_71.lib",
        "libboost_coroutine-vc142-mt-sgd-x64-1_71.lib"
    }

    prelinkcommands {
        ("{COPY} res %{gamebin}"),
        ("{COPY} %{enginebin}/*.dll %{gamebin}")
    }

    filter { "configurations:Debug", "toolset:gcc" }
        buildoptions { "-std=c++17", "-Wall", "-fmax-errors=4", "-Wfatal-errors" }

    filter { "configurations:Release", "toolset:gcc" }
        buildoptions { "-O2", "-std=c++17" }
        linkoptions { "-s -mwindows"}
        links { "mingw32" }

    filter "system:windows"
		systemversion "latest"
		defines {
			"SE_PLATFORM_WINDOWS"
		}

    configuration "Debug"
        defines "SE_DEBUG"
        runtime "Debug"
        symbols "On"
        -- buildoptions "/MTd"

    configuration "Release"
        defines "SE_RELEASE"
        runtime "Release"
        optimize "On"
        -- buildoptions "/MT"

    configuration "Dist"
        defines "SE_DIST"
        runtime "Release"
        optimize "On"
        -- buildoptions "/MT"



