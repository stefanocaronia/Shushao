project 'Box2D'
    basedir ("Box2D")
    kind 'StaticLib'
    cppdialect 'C++11'

    targetdir ("%{prj.location}/lib/" .. outputdir .. "/%{prj.name}")
    objdir ("%{prj.location}/obj/" .. outputdir .. "/%{prj.name}")

    files { '%{prj.location}/Box2D/**' }
    includedirs { '%{prj.location}/.' }

    configuration { "gmake2" }
        targetextension (".a")

    filter { "configurations:Release", "toolset:gcc" }
        buildoptions { "-O2", "-std=c++17" }
        linkoptions { "-s -mwindows"}

    filter { "configurations:Debug", "toolset:gcc" }
        buildoptions { "-std=c++17", "-Wall", "-fmax-errors=4", "-Wfatal-errors" }

    -- makesettings [[
    --     CC = g++
    -- ]]

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        defines { '_CRT_SECURE_NO_WARNINGS', '_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH' }

    filter { "system:windows", "configurations:Debug" }
        defines "DEBUG"
        runtime "Debug"
        symbols "On"
        buildoptions "/MTd"

    filter { "system:windows", "configurations:Release" }
        defines "NDEBUG"
        runtime "Release"
        optimize "On"
        buildoptions "/MT"