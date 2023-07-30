## Using vcpkg as a package manager for a project

## If you want to use vcpkg as a submodule:

```bash
git submodule add https://github.com/Microsoft/vcpkg.git vendor/vcpkg
git submodule init
git submodule update
git pull --recurse-submodules
```
* Copy the two .bat files into your project directory
* `vcpkg-install.bat` will first execute `vcpkg-boot.bat` if vcpkg is not found

## If you want to clone vcpkg into the project without using a submodule:

* Run `vcpkg-boot.bat` directly, it will do everything
* alternatively, you can use:
```bash
git clone https://github.com/Microsoft/vcpkg.git vendor/vcpkg
```

## If you want to use a global vcpkg:

* Clone vcpkg wherever you want

```bash
git clone https://github.com/Microsoft/vcpkg.git
```
* Add the path to the Windows PATH
* Modify `vcpkg-install.bat` by uncommenting the part with `:: With global vcpkg installation` and commenting out the section under `:: With local vcpkg installation`
* Do not use `vcpkg-boot.bat`

## Update

Every time you need an update, simply run:

```bash
.\vcpkg-install.bat
```

To do the vcpkg bootstrap (creation of exe) run:

```bash
.\vcpkg-boot.bat
```
