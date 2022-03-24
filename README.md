# Termi
(Termi currently is just a terminal app but we are developing it to be a fully working terminal not just an app)

**From now, non-OpenGL version will not be supported!**

**If you want use non-OpenGL version, manually install files!**

A Powerful Terminal made in C++

## About Termi
- Termi is a powerful terminal made using C++.
- It can run on Windows, macOS and GNU/Linux.
- The goal of Termi is create independent terminal.
- ```Independent``` mean to be independent from terminal in operating system i.e. a separate kind of terminal use "own" GUI renedering system.
- We accept contibutors, create a **Pull Request** to contribute and check [our coding style](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#coding-sytle-for-pull-requests)
- And plese read [organize part](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#code-organization) which talk about directory organization.

## Checklist
### Termi base C++ part
- [x] Windows version
- [x] GNU/Linux version
- [x] macOS version (same folder/directory as GNU/Linux version, unsupported)

### Termi C++ part
- [ ] User settings in JSON files
- [ ] Support most of major commands
- [ ] Include other host terminals
- [ ] Arguments

### Windows - installer and launcher
- [x] Installer in [Inno Setup](https://github.com/jrsoftware/issrc)
- [x] Lanucher and updater - C#

### Independence
- [x] Independence (Windows & GNU/Linux [ImGui](https://github.com/ocornut/imgui) base)
- [x] Independence (Windows & GNU/Linux [ImGui](https://github.com/ocornut/imgui))
- [ ] Independence (Windows & GNU/Linux [ImGui](https://github.com/ocornut/imgui) real console and changing font)

## Build & Run
### Required software:
- Visual Studio 2019 or Visual Studio 2022, ```Desktop development with C++``` and ```.NET 5.0 Runtime``` components (if you use Visual Studio 2012, add support for Visual Studio 2019) - Windows.
- g++ complier - GNU/Linux
  - Install with ```sudo apt-get install g++``` if not already installed on GNU/Linux machine.
- build-essential - GNU/Linux
  - Install with ```sudo apt-get install build-essential``` if not already installed on GNU/Linux machine.
- CMake
  - Install with ```sudo apt-get install cmake``` if not already installed on GNU/Linux machine.
- Git
  - Install with ```sudo apt-get install git``` if not already installed on GNU/Linux machine.
- OpenGL - for OpenGL project part
  - Check [this video](https://www.youtube.com/watch?v=643CUhCoyCo) to install it on GNU/Linux machine.
- curl - for Package Manager
  - Instal with ```sudo apt-get install curl libcurl4-openssl-dev``` if not already installed on GNU/Linux machine.

### Build & Run - Windows
- Open ```Developer Command Prompt for VS 2019``` or ```Developer Command Prompt for VS 2022``` and run ```compile.bat``` in `Termi-Windows\Termi\x64\Release` directory.
- Open Termi Visual Studio Solution and compile it.
- If you running application from Visual Studio, loading executables won't work because running from ```Release``` folder/directory isn't same as running from Visual Studio!
- Also you can build launcher and installer for Windows version too :)
- If you want run Termi as standard user, check latest release and download executable or simply clone repo and update it with ```git pull```. You can also use [installer](https://github.com/ringwormGO-organization/Termi/blob/main/Termi-Windows/Installer/Termi.exe) but you need still need to download ```MSVC C++ runtime enviroment```b and ```.NET 5.0 Runtime```. It is recommended that you run the application as an administrator, especially if launcher downloading new update because writing to ```C:\Programs Files``` or similiar directory require administartor priviliges.

### Build & Run - GNU/Linux version (& macOS version which unsupported)
```sh
$ cd Termi-Linux && chmod +x ./compile.sh && ./compile.sh
```
from root directory.

### Build & Run (OpenGL)
1. For Windows open Visual Studio solution and compile it. If you compile can't compile project check Victor's video on installing OpenGL (first public video on channel) and video about OpenGL and GLFW.
2. For GNU/Linux type: ```cmake . && make && ./Termi-OpenGL```. If you can't compile project try with: ```cmake && sudo make && ./Termi-OpenGL```. If you still can't compile project check [this video](https://www.youtube.com/watch?v=643CUhCoyCo).

### Build & Run - Package Manager
1. For Windows open terminal and type ```cmake .``` and open Visual Studio solution, compile it. If you get error about ```ALL_BUILD``` project, ignore it and find executable file in ```Debug``` folder.
2. For Linux open terminal and type ```cmake . && make && pkg [arguments]```.

## Development picture
![image](https://user-images.githubusercontent.com/83548580/159910200-8fa25e94-ba38-4b34-a84c-21d48f381603.png)

Termi-OpenGL running on GNU/Linux, Lubuntu 21.10 distribution

## External dependencies
- [OpenGL](https://www.opengl.org/)
- [ImGui](https://github.com/ocornut/imgui)
- [stb](https://github.com/nothings/stb)
- [curl](https://github.com/curl/curl)

## Credits
- [Background launcher picture](https://pixabay.com/photos/leaf-maple-autumn-foliage-botany-3865014/)
- [Stack Overflow](https://stackoverflow.com/) - solution for most of problems
- [Cherno](https://www.youtube.com/c/TheChernoProject) - for recommended ImGUI
- [Victor Gordan](https://www.youtube.com/c/VictorGordan) - for OpenGL window code
- [cppfetch](https://github.com/Phate6660/cppfetch) - for Termi's `neofetch`
- Other artcicles on internet
____________________________________

Thank you for choosing Termi.

© 2022 ringwormGO
