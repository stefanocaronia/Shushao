project "Glad"
    basedir ("Glad")
    kind "StaticLib"
    targetname "libGlad"

    targetdir ("%{prj.location}/lib")
    objdir ("%{prj.location}/obj")

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
        staticruntime "On"

    configuration "Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"
        buildoptions "/MTd"

    configuration "Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "On"
        buildoptions "/MT"