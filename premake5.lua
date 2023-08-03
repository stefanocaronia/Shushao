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

    vcpkg_root = "../vendor/vcpkg"
    vcpkg_triplet = "x64-windows-static"
    vcpkg_manifest = "vcpkg.json"
    vcpkg_use_static_libraries = true
    vcpkg_installed_packages = "installed"

    IncludeDir = {}
    -- IncludeDir["packages"] = "%{vcpkg_root}/installed/%{vcpkg_triplet}/include";

    LibDir = {}
    -- LibDir["packages"] = "%{vcpkg_root}/installed/%{vcpkg_triplet}/lib";

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
        "%{prj.name}/vendor/external",
        -- "%{IncludeDir.packages}"
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
    staticruntime "on"

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
        -- "%{IncludeDir.packages}"
    }

    -- libdirs {
        -- "%{LibDir.packages}"
    -- }

    links {
        Engine,
        -- "glfw3",
        -- "Glad",
        -- "SOIL2",
        -- "Box2D",
        -- "freetype",
        -- "spdlog",
        -- "imgui",
        -- "opengl32"
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



