project "ImGui"
    basedir ("imgui")
    kind "StaticLib"
    language "C++"

    targetdir ("%{prj.location}/lib/" .. outputdir .. "/%{prj.name}")
    objdir ("%{prj.location}/obj/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/*.h",
        "%{prj.location}/*.cpp",
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"

    filter { "system:windows", "configurations:Debug" }
        buildoptions "/MTd"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"