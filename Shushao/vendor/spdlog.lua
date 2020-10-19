project "spdlog"
    basedir ("spdlog")
    kind "StaticLib"
    language "C++"
    cppdialect "C++11"
    staticruntime "On"

    targetdir ("%{prj.location}/lib/" .. outputdir)
    objdir ("%{prj.location}/obj/" .. outputdir)

    files {
        "%{prj.location}/include/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/include"
    }

    defines { "SPDLOG_COMPILED_LIB" }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "On"