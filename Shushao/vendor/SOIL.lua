project "SOIL2"
    basedir ("SOIL")
    kind "StaticLib"
    language "C++"
    staticruntime "On"

    -- buildoptions { "/TP" }
    defines { "_CRT_SECURE_NO_WARNINGS" }

    targetdir ("%{prj.location}/lib/" .. outputdir)
    objdir ("%{prj.location}/obj/" .. outputdir)

    files { "%{prj.location}/src/SOIL2/*.c" }

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