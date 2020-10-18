project "Glad"
    basedir ("Glad")
    kind "StaticLib"
    targetname "libGlad"

    targetdir ("%{prj.location}/lib/" .. outputdir .. "/%{prj.name}")
    objdir ("%{prj.location}/obj/" .. outputdir .. "/%{prj.name}")

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

    filter { "system:windows", "configurations:Debug" }
        symbols "On"
        buildoptions "/MTd"

    filter { "system:windows", "configurations:Release" }
        optimize "On"
        buildoptions "/MT"