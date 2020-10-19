project "Glad"
    basedir ("Glad")
    kind "StaticLib"
    targetname "libGlad"
    staticruntime "On"

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

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "On"