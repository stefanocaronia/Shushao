@echo off

echo.
echo * Installing vcpkg locally *
echo.

findstr /m /c:"path = vendor/vcpkg" .gitmodules
if errorlevel 1 (
    if exist .\vendor\vcpkg\.git (
        echo vcpkg found, updating...
        cd .\vendor\vcpkg
        git pull
        cd ../..
    ) else (
        echo vcpkg not found, cloning...
        git clone https://github.com/Microsoft/vcpkg.git .\vendor\vcpkg
    )
) else (
    echo vcpkg is a submodule, initializing and updating...
    git submodule update --init -- vendor\vcpkg
)

if not exist .\vendor\vcpkg\vcpkg.exe (
    @call .\vendor\vcpkg\bootstrap-vcpkg.bat
)