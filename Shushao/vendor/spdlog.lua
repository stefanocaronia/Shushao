project "spdlog"
    basedir ("spdlog")
    kind "StaticLib"
    language "C++"
    cppdialect "C++11"

    targetdir ("%{prj.location}/lib/" .. outputdir .. "/%{prj.name}")
    objdir ("%{prj.location}/obj/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/include/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/include"
    }

    defines { "SPDLOG_COMPILED_LIB" }

    filter { "system:windows", "configurations:Debug" }
        buildoptions "/MTd"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"