project "Box2D"
    basedir ("Box2D")
    kind "StaticLib"
    cppdialect "C++11"
    staticruntime "on"

    targetdir ("%{prj.location}/lib/" .. outputdir)
    objdir ("%{prj.location}/obj/" .. outputdir)

    files { "%{prj.location}/Box2D/**" }
    includedirs { "%{prj.location}/." }

    configuration { "gmake2" }
        targetextension (".a")

    filter { "configurations:Release", "toolset:gcc" }
        buildoptions { "-O2", "-std=c++17" }
        linkoptions { "-s -mwindows"}

    filter { "configurations:Debug", "toolset:gcc" }
        buildoptions { "-std=c++17", "-Wall", "-fmax-errors=4", "-Wfatal-errors" }

    filter "system:windows"
        systemversion "latest"
        defines {
            "_CRT_SECURE_NO_WARNINGS",
            "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH"
        }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"