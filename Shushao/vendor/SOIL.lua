project "SOIL2"
    basedir ("SOIL")
    kind "StaticLib"
    language "C++"

    buildoptions { "/TP" }
    defines { "_CRT_SECURE_NO_WARNINGS" }

    targetdir ("%{prj.location}/lib/" .. outputdir .. "/%{prj.name}")
    objdir ("%{prj.location}/obj/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.location}/src/SOIL2/*.c" }

    filter { "system:windows", "configurations:Debug" }
        symbols "On"
        buildoptions "/MTd"

    filter { "system:windows", "configurations:Release" }
        optimize "On"
        buildoptions "/MT"