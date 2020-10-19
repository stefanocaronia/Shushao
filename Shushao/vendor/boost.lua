project "Boost"
    basedir ("boost")
    kind "StaticLib"

    targetdir ("%{prj.location}/stage/lib")
    objdir ("%{prj.location}/stage/lib")

    configuration { "action:gmake2" }
        prebuildcommands {
            "./b2 headers",
            "./b2 toolset=gcc --build-type=complete stage cxxflags=\"-std=c++17\" -mt --with-coroutine"
        }

    -- example builds
    -- (path.translate("bjam toolset=msvc link=static threading=multi address-model=64 runtime-link=static --with-coroutine stage"))
    -- (path.translate("bjam -j8 toolset=msvc --variant=release --link=static --runtime-link=static --build-type=complete cxxflags=\"/std:c++17\" -mt --with-coroutine stage"))
    -- (path.translate("bjam -j8 toolset=msvc --build-type=complete cxxflags=\"/std:c++17\" -mt --with-coroutine stage")),
    -- (path.translate("bjam -j8 --toolset=msvc-14.1 --link=static --threading=multi --build-type=minimal --with-coroutine stage")),

    cleancommands {
        (path.translate("bjam --clean"))
    }

    configuration { "system:windows" }
        prebuildcommands {
            "IF NOT EXIST \"bin.v2\" (bootstrap.bat)"
        }
        postbuildcommands {
            (path.translate("bjam headers")),
        }

    configuration { "system:windows", "action:vs2019", "configurations:Release" }
        postbuildcommands {
            (path.translate("bjam toolset=msvc --variant=release link=static threading=multi address-model=64 runtime-link=static --with-coroutine stage"))
        }

    filter { "system:windows", "action:vs2019", "configurations:Debug" }
        postbuildcommands {
            (path.translate("bjam toolset=msvc --variant=debug link=static threading=multi address-model=64 runtime-link=static --with-coroutine stage"))
        }


