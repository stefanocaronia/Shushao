project "Glad"
    basedir ("Glad")
    kind "StaticLib"
    targetname "libGlad"
    staticruntime "on"

    targetdir ("%{prj.location}/lib/" .. outputdir)
    objdir ("%{prj.location}/obj/" .. outputdir)

    makesettings [[
        CC = gcc
    ]]

    -- configuration { "gmake2" }
    --     targetextension (".a")

    files {
        "%{prj.location}/include/glad/glad.h",
        "%{prj.location}/include/KHR/khrplatform.h",
        "%{prj.location}/src/glad.c"
    }

    includedirs {
        "%{prj.location}/include"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"