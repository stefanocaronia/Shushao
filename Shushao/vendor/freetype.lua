project 'Freetype'
    basedir ("freetype")
    kind 'StaticLib'
    language "C"
    staticruntime "on"

    targetdir ("%{prj.location}/lib/" .. outputdir)
    objdir ("%{prj.location}/obj/" .. outputdir)

    files {
        "%{prj.location}/src/autofit/autofit.c",
        "%{prj.location}/src/base/ftbase.c",
        "%{prj.location}/src/base/ftinit.c",
        "%{prj.location}/src/base/ftsystem.c",
        "%{prj.location}/src/bdf/bdf.c",
        "%{prj.location}/src/cache/ftcache.c",
        "%{prj.location}/src/cff/cff.c",
        "%{prj.location}/src/cid/type1cid.c",
        "%{prj.location}/src/gzip/ftgzip.c",
        "%{prj.location}/src/lzw/ftlzw.c",
        "%{prj.location}/src/pfr/pfr.c",
        "%{prj.location}/src/pcf/pcf.c",
        "%{prj.location}/src/psaux/psaux.c",
        "%{prj.location}/src/pshinter/pshinter.c",
        "%{prj.location}/src/psnames/psmodule.c",
        "%{prj.location}/src/raster/raster.c",
        "%{prj.location}/src/sfnt/sfnt.c",
        "%{prj.location}/src/smooth/smooth.c",
        "%{prj.location}/src/truetype/truetype.c",
        "%{prj.location}/src/type1/type1.c",
        "%{prj.location}/src/type42/type42.c",
        "%{prj.location}/src/winfonts/winfnt.c",
        "%{prj.location}/builds/windows/ftdebug.c",
        "%{prj.location}/src/base/ftbbox.c",
        "%{prj.location}/src/base/ftbdf.c",
        "%{prj.location}/src/base/ftbitmap.c",
        "%{prj.location}/src/base/ftcid.c",
        "%{prj.location}/src/base/ftfstype.c",
        "%{prj.location}/src/base/ftgasp.c",
        "%{prj.location}/src/base/ftglyph.c",
        "%{prj.location}/src/base/ftgxval.c",
        "%{prj.location}/src/base/ftmm.c",
        "%{prj.location}/src/base/ftotval.c",
        "%{prj.location}/src/base/ftpatent.c",
        "%{prj.location}/src/base/ftpfr.c",
        "%{prj.location}/src/base/ftstroke.c",
        "%{prj.location}/src/base/ftsynth.c",
        "%{prj.location}/src/base/fttype1.c",
        "%{prj.location}/src/base/ftwinfnt.c",
        "%{prj.location}/src/base/ftver.rc"
    }

    includedirs {
        "%{prj.location}/include"
    }

    links {
        "kernel32.lib",
        "user32.lib",
        "gdi32.lib",
        "winspool.lib",
        "comdlg32.lib",
        "advapi32.lib",
        "shell32.lib",
        "ole32.lib",
        "oleaut32.lib",
        "uuid.lib",
        "odbc32.lib",
        "odbccp32.lib"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "FT2_BUILD_LIBRARY"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
