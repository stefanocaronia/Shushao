project "SOIL2"
    basedir ("SOIL")
    kind "StaticLib"
    language "C++"

    buildoptions { "/TP" }
    defines { "_CRT_SECURE_NO_WARNINGS" }

    targetdir ("%{prj.location}/lib")
    objdir ("%{prj.location}/obj")

    files { "%{prj.location}/src/SOIL2/*.c" }

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