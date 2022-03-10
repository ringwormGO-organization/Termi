# Termi
(Termi currently is just a terminal app but we are developing it to be a fully working terminal not just an app)

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

### Independence
- [x] Independence (Windows & GNU/Linux [ImGUI](https://github.com/ocornut/imgui) base)
- [ ] Independence (Windows & GNU/Linux [ImGUI](https://github.com/ocornut/imgui))

## Build & Run
### Required software:
- Visual Studio 2019 or Visual Studio 2022 and ```Desktop development with C++``` components (if you use Visual Studio 2019, add support for Visual Studio 2019) - Windows.
- G++ complier - GNU/Linux
  - Install with ```sudo apt-get install g++``` if not already installed on GNU/Linux machine.
- CMake
  - Install with ```sudo apt-get install cmake``` if not already installed on GNU/Linux machine.
- Git
  - Install with ```sudo apt-get install git``` if not already installed on GNU/Linux machine.
- OpenGL - for OpenGL project part
  - Check [this video](https://www.youtube.com/watch?v=643CUhCoyCo) to install it on GNU/Linux machine.

### Build & Run - Windows
- Open ```Developer Command Prompt for VS 2019``` or ```Developer Command Prompt for VS 2022``` and run ```compile.bat``` in `Termi-Windows\Termi\x64\Release` directory.
- Open Termi Visual Studio Solution and compile it.
- If you want run Termi as standard user, check latest release and download executable or simply clone repo and update it with ```git pull```. You can also use [installer](https://github.com/ringwormGO-organization/Termi/blob/main/Termi-Windows/Installer/Termi.exe).
- If you running application from Visual Studio, loading executables won't work because running from ```Release``` folder/directory isn't same as running from Visual Studio!

### Build & Run - GNU/Linux version (& macOS version which unsupported)
```sh
$ cmake . && make`
```
or
```sh
$ chmod +x ./build.sh && ./build.sh
```
from root directory.

### Build & Run (OpenGL)
1. For Windows open Visual Studio solution and compile it. If you compile can't compile project check Victor's video on installing OpenGL (first public video on channel) and video about OpenGL and GLFW.
2. For GNU/Linux type: ```cmake . && make && ./Termi-OpenGL```. If you can't compile project try with: ```cmake && sudo make && ./Termi-OpenGL```. If you still can't compile project check [this video](https://www.youtube.com/watch?v=643CUhCoyCo).

### Build & Run - Package Manager
1. For Windows open terminal and type ```cmake .``` and open Visual Studio solution, compile it. If you get error about ```ALL_BUILD``` project, ignore it and find executable file in ```Debug``` folder.
2. For Linux open terminal and type ```cmake . && make && pkg [arguments]```.

## Development picture
![image](https://user-images.githubusercontent.com/83548580/157011432-f1dc9427-e490-4873-919b-ee0e927bd549.png)

Termi-OpenGL running on Windows 11 Pro 21H2

## External dependencies
- [OpenGL](https://www.opengl.org/)
- [ImGUI](https://github.com/ocornut/imgui)
- [stb](https://github.com/nothings/stb)

## Credits
- [Stack Overflow](https://stackoverflow.com/) - solution for most of problems
- [Cherno](https://www.youtube.com/c/TheChernoProject) - for recommended ImGUI
- [Victor Gordan](https://www.youtube.com/c/VictorGordan) - for OpenGL window code
____________________________________

Thank you for choosing Termi.

© 2022 ringwormGO
