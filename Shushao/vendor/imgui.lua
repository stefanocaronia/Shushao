project "ImGui"
    basedir ("imgui")
    kind "StaticLib"
    language "C++"
    staticruntime "On"

    targetdir ("%{prj.location}/lib/" .. outputdir)
    objdir ("%{prj.location}/obj/" .. outputdir)

    files {
        "%{prj.location}/*.h",
        "%{prj.location}/*.cpp",
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "On"