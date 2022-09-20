# Termi

(Windows version might will be synced once in each week)

**From now, non-OpenGL version will not be supported!**

**If you want use non-OpenGL version, manually install files from commits history!**

A Powerful Terminal made in C++ with OpenGL and ImGui with own commands

## About Termi
- Termi is a powerful terminal made using C++.
- It can run on Windows, macOS and GNU/Linux, BSD and all other platforms which support C++ standard library well as other platforms and GLFW
- Have own commands.
- The goal of Termi is create independent terminal.
- ```Independent``` mean to be independent from terminal in operating system i.e. a separate kind of terminal use "own" GUI renedering system.
- We accept contibutors, create a **Pull Request** to contribute and check [our coding style](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#coding-sytle-for-pull-requests)
- And plese read [organize part](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#code-organization) which talk about directory organization.
- Currently there is only one [stable release](https://github.com/ringwormGO-organization/Termi/releases/tag/v1.0.0).
- [Commands list and explanation](https://github.com/ringwormGO-organization/Termi/blob/main/Commands.md)

## Checklist
### Termi base part
- [x] Windows version
- [x] GNU/Linux version
- [x] BSD version (same folder/directory as GNU/Linux version, moderately supported)
- [x] macOS version (same folder/directory as GNU/Linux version, unsupported)
- [ ] Windows generator (rewrite, in Python programming language)

### Termi advanced C++ part
- [x] User settings in text files
- [ ] User settings in JSON
- [x] Support most of major commands
- [x] Arguments
- [ ] Loading executables (.dll files for Windows, .so files for macOS, GNU/Linux, BSD, etc.)
- [x] Colors in console
- [x] Translation (may not be fully finished in v2.0.0)

### Windows - installer and launcher
- [x] Installer in [Inno Setup](https://github.com/jrsoftware/issrc)
- [x] Lanucher and updater - C#

## Build & Run
### Required software:
### Windows
- Visual Studio 2019 or Visual Studio 2022, ```Desktop development with C++```, ```.NET 5.0 Runtime``` and ```.NET 6 Runtime``` components (if you use Visual Studio 2022, add support for Visual Studio 2019) - Windows.

### Other
- g++ complier
  - Install with ```apt-get install gcc g++``` if not already installed on GNU/Linux machine, Debain based.
  - Install with ```pacman -S gcc g++``` if not already installed on GNU/Linux machine, Arch based.
- build-essential
  - Install with ```apt-get install build-essential``` if not already installed on GNU/Linux machine, Debain based.
  - Install with ```pacman -S base-devel``` if not already installed on GNU/Linux machine, Arch based.
- CMake
  - Install with ```apt-get install cmake``` if not already installed on GNU/Linux machine, Debain based.
  - Install with ```pacman -S cmake``` if not already installed on GNU/Linux machine, Arch based.
- OpenGL - for OpenGL project part
  - Check [this video](https://www.youtube.com/watch?v=CIbJ5Iw0yAs) to install it on GNU/Linux machine
  - For BSD based operating systems, process should be similar, just when you are done with compiling GLFW, copy header files to `/usr/include/GLFW`
  and copy `libglfw.so` and `libGL.so` to `/usr/lib/`

### Both
- Git - for cloning repo
  - Check Git website for Windows instructions or do `winget install git`
  - Install with ```apt-get install git``` if not already installed on GNU/Linux machine, Debain based.
  - Install with ```pacman -S git``` if not already installed on GNU/Linux machine, Arch based.
- Python3 - required for tools
  - Install with ```apt-get install python3``` if not already installed on GNU/Linux machine, Debain based.
  - Install with ```pacman -S python3``` if not already installed on GNU/Linux machine, Arch based.
  
**Commands which requires package installation have to be runned with administartor/root access!**

### Build & Run - Windows
1. Build `Termi-GUI` project and copy from `Termi-GUI/x64/Debug` `Termi-GUI.dll` file into `Termi-Main/bin/debug/net6.0`.
2. Then copy from `Termi-Commands/x64/Debug` copy `Termi-Commands.dll` file into `Termi-Main/bin/debug/net6.0` folder/directory.
3. Build `Termi-Main` project and run executable

### Build & Run (OpenGL)
1. For Windows open Visual Studio solution and compile it. If you compile can't compile project check Victor's video on installing OpenGL (first public video on channel) and video about OpenGL and GLFW.
2. For GNU/Linux (macOS, BSD, unsupported) type: ```cmake . && make && ./Termi-OpenGL```. If you can't compile project try with: ```cmake && make && ./Termi-OpenGL```. If you still can't compile project check [this video](hhttps://www.youtube.com/watch?v=CIbJ5Iw0yAs), check description of video!

## Known issues
- OpenGL might now open when reading from .txt file, remove `render->Settings(1, 0)` and `render->Settings(2, 0)` to size which you want
- Dear ImGui might cause segmentation fault on BSD based operating systems **(we are fixing this currently)**

## Development picture
![image](https://user-images.githubusercontent.com/83548580/190228798-b568230d-fe73-4021-8130-96b921741303.png)

Termi-OpenGL running on GNU/Linux, Arch Linux (pictures may late)

## External dependencies
- [OpenGL](https://www.opengl.org/)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [stb](https://github.com/nothings/stb)
- [dirent](https://github.com/tronkko/dirent) - ```dirent.h``` for Windows

## Credits
- [Background launcher picture](https://pixabay.com/photos/leaf-maple-autumn-foliage-botany-3865014/)
- [Stack Overflow](https://stackoverflow.com/) - solution for most of problems
- [Cherno](https://www.youtube.com/c/TheChernoProject) - he recommended Dear ImGui to us
- [Victor Gordan](https://www.youtube.com/c/VictorGordan) - for OpenGL window code
- [cppfetch](https://github.com/Phate6660/cppfetch) - for Termi's `neofetch`
- Other artcicles about programming (web format, books, etc.)
____________________________________

Thank you for choosing Termi.

© 2021 - present ringwormGO
