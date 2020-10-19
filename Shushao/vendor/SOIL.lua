project "SOIL2"
    basedir ("SOIL")
    kind "StaticLib"
    language "C++"
    staticruntime "On"

    buildoptions { "/TP" }
    defines { "_CRT_SECURE_NO_WARNINGS" }

    targetdir ("%{prj.location}/lib/" .. outputdir)
    objdir ("%{prj.location}/obj/" .. outputdir)

    files { "%{prj.location}/src/SOIL2/*.c" }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "On"