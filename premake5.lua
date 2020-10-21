workspace "Shushao"
	architecture "x64"
    startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
    }

    outputdir = "%{cfg.buildcfg}"
    Sandbox = "Sandbox"
    Engine = "Shushao"
    sandbox_bin = "../bin/" .. outputdir .. "/%{Sandbox}/"
    engine_bin = "../bin/" .. outputdir .. "/%{Engine}/"

    IncludeDir = {}
    IncludeDir["GLFW"] = "%{Engine}/vendor/GLFW/include";
    IncludeDir["Glad"] = "%{Engine}/vendor/Glad/include";
    IncludeDir["SOIL"] = "%{Engine}/vendor/SOIL/include";
    IncludeDir["spdlog"] = "%{Engine}/vendor/spdlog/include";
    IncludeDir["freetype"] = "%{Engine}/vendor/freetype/include";
    IncludeDir["glm"] = "%{Engine}/vendor/glm";
    IncludeDir["boost"] = "%{Engine}/vendor/boost";
    IncludeDir["Box2D"] = "%{Engine}/vendor/Box2D";
    IncludeDir["ImGui"] = "%{Engine}/vendor/imgui";

    group "Dependencies"
        include "Shushao/vendor/Box2D.lua"
        include "Shushao/vendor/boost.lua"
        include "Shushao/vendor/freetype.lua"
        include "Shushao/vendor/Glad.lua"
        include "Shushao/vendor/GLFW.lua"
        include "Shushao/vendor/SOIL.lua"
        include "Shushao/vendor/spdlog.lua"
        include "Shushao/vendor/imgui.lua"
    group ""

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
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.frag",
        "%{prj.name}/src/**.vert"
	}

    includedirs {
        "%{prj.name}/src",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.SOIL}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.freetype}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.boost}",
        "%{IncludeDir.Box2D}",
        "%{IncludeDir.ImGui}"
    }

    -- defines {
    --     "_CRT_SECURE_NO_WARNINGS"
    -- }

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

    filter "configurations:Debug"
        defines "SE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "SE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "SE_DIST"
        runtime "Release"
        optimize "On"


project "Shushao Resources"
    location "Shushao"
    kind "SharedLib"
    targetname "shushaores"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/Shushao")
    objdir ("obj/" .. outputdir .. "/Shushao")

    files {
        "Shushao/src/Shushao/Resources/**.h",
        "Shushao/src/Shushao/Resources/**.rc"
    }

    postbuildcommands {
        ("{COPY} %{engine_bin}/*.dll %{sandbox_bin}")
    }

    linkoptions "/NOENTRY"

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"

    filter "configurations:Release"
        runtime "Release"

project "Sandbox"
	location "Sandbox"
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
        "%{prj.name}/src",
        "%{Engine}/src",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.SOIL}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.freetype}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.boost}",
        "%{IncludeDir.Box2D}",
        "%{IncludeDir.ImGui}"
    }

    libdirs {
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
        "imgui",
        "opengl32",
        "libboost_context-vc142-mt-sgd-x64-1_71",
        "libboost_coroutine-vc142-mt-sgd-x64-1_71"
    }

    prelinkcommands {
        ("{COPY} res %{sandbox_bin}"),
        ("{COPY} %{engine_bin}/*.dll %{sandbox_bin}")
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
			"SE_PLATFORM_WINDOWS",
            -- "_CRT_SECURE_NO_WARNINGS"
		}

    filter "configurations:Debug"
        defines "SE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "SE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "SE_DIST"
        runtime "Release"
        optimize "On"



