project 'Box2D'
    basedir ("Box2D")
    kind 'StaticLib'
    cppdialect 'C++11'

    targetdir ("%{prj.location}/lib")
    objdir ("%{prj.location}/obj")

    files { '%{prj.location}/Box2D/**' }
    includedirs { '%{prj.location}/.' }

    -- configuration { "gmake2" }
    --     targetextension (".a")

    makesettings [[
        CC = g++
    ]]

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

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        defines { '_CRT_SECURE_NO_WARNINGS', '_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH' }
