@echo off
set target=vs2019

echo.
echo * premake5 Generating Projects for target %target% *
echo.

@call vendor\premake5\bin\premake5.exe %target%
echo.

:: targets:
    : vs2019
    : codeblocks
    : gmake2