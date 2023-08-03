@echo off

:: With local vcpkg installation
if not exist .\vendor\vcpkg\vcpkg.exe (
    @call .\vcpkg-boot.bat
)
cd .\vendor\vcpkg
:: .\vcpkg x-update-baseline --add-initial-baseline
.\vcpkg x-update-baseline
.\vcpkg install --x-install-root=.\installed --triplet x64-windows-static
cd ..\..

:: ----------------------------------------------------------------------------
:: With global vcpkg installation
:: :: vcpkg x-update-baseline --add-initial-baseline
:: vcpkg x-update-baseline
:: vcpkg install --x-install-root=.\vendor\vcpkg\installed --triplet x64-windows


