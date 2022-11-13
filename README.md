# Termi
**If you want use non-OpenGL version, manually install files from commits history!**

**Syncing Windows version may not be regular!**

**[Latest stable release](https://github.com/ringwormGO-organization/Termi/releases/tag/v2.0.0)**

A Powerful terminal made in C++ with OpenGL and Dear ImGui with own commands

## About Termi
- Termi is a powerful terminal written in C++.
- It can run on Windows, macOS and GNU/Linux, BSD and all other platforms which support C++ standard library, something like .dll and .so files and GLFW
- The goal of Termi is create independent terminal, i.e. a separate kind of terminal use "own" GUI renedering system.
- Has own commands that can be written using C, C++ or Rust.
- We accept contibutors; create a **Pull Request** to contribute and check [our coding style](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#coding-sytle-for-pull-requests)
- [Commands list and explanation](https://github.com/ringwormGO-organization/Termi/blob/main/Commands.md)
- And plese read [organize part](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#code-organization) which talk about directory organization.

## Releases
- [v1.0.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v1.0.0).
- [Latest release (v2.0.0)](https://github.com/ringwormGO-organization/Termi/releases/tag/v2.0.0)

## Checklist
### Termi base part
- [x] Windows version (moderately supported)
- [x] GNU/Linux version (in `Termi-Other` folder/directory)
- [x] BSD version (same folder/directory as GNU/Linux version, moderately supported)
- [x] macOS version (same folder/directory as GNU/Linux version, unsupported)

### Termi advanced C++ part
- [x] Arguments
- [x] Better arguments for Rust commands/applications
- [x] Colors in console
- [ ] GUI models (for better input system) (planned for v3.0.0)
- [x] Loading executables (.dll files for Windows, .so files for macOS, GNU/Linux, BSD, etc.)
- [x] Most of major commands
- [ ] Networking (package manager, SSH) (planned for v3.0.0)
- [x] Translations
- [x] User settings in JSON
- [ ] UTF-8 support

### Windows - installer and launcher
- [x] Installer in [Inno Setup](https://github.com/jrsoftware/issrc)
- [x] Lanucher and updater - C#

## Build & Run
### Required software:
### Windows
- Visual Studio Visual Studio 2022, ```Desktop development with C++```, ```.NET 5.0 Runtime``` and ```.NET 6 Runtime``` components - Windows.

### Other versions
- g++ complier
  - Install with ```apt-get install gcc g++``` if not already installed on GNU/Linux machine, Debain based.
  - Install with ```pacman -S gcc g++``` if not already installed on GNU/Linux machine, Arch based.
- build-essential
  - Install with ```apt-get install build-essential``` if not already installed on GNU/Linux machine, Debain based.
  - Install with ```pacman -S base-devel``` if not already installed on GNU/Linux machine, Arch based.
- CMake
  - Install with ```apt-get install cmake``` if not already installed on GNU/Linux machine, Debain based.
  - Install with ```pacman -S cmake``` if not already installed on GNU/Linux machine, Arch based.
- json-c library
  - Install with `apt-get install libjson-c-dev` if not already installed on GNU/Linux machine, Debain based.
  - Install with `pacman -S json-c` if not already installed on GNU/Linux machine, Debain based.

### Both versions
- Git - for cloning repo
  - Check Git website for Windows instructions or do `winget install git`
  - Install with ```apt-get install git``` if not already installed on GNU/Linux machine, Debain based.
  - Install with ```pacman -S git``` if not already installed on GNU/Linux machine, Arch based.

- OpenGL - for OpenGL project part
  - ### Windows
    - Visual Studio 2022 solution should work without any additional configuration.
    - If it doesn't work, see following instructions down below:
      - open properties of `Termi-GUI` project,
      - goto `VC++ Directories`,
      - set your path (they are bundled with Termi (they are in `Libraries` folder/directory), but Visual Studio knows to set entire path (user directory, etc. so you need to change them)) of `Include Directories` and `Library Directories`
  - ### Other platforms (macOS, (GNU/)Linux, BSD)
    - Check [this video](https://www.youtube.com/watch?v=CIbJ5Iw0yAs) to install it on (GNU/)Linux machine

    - For BSD based operating systems, follow instructions down below (it is pretty much same):
      - download glad header files (see video for more details),
      - place them in `/usr/include` (see video for more details),
      - compile GLFW,
      - copy GLFW header files to `/usr/include/GLFW`,
      - copy `libglfw.so` and `libGL.so` to `/usr/lib/`.

    - Or you can **try** to use header files included with Termi, see instructions down below:
      - check are they in `Termi-Other/Termi-GUI/includes`,
      - install or compile GLFW package through your package manager,
      - enable such option in `Settings.hpp`.

- Rust - required for building Rust commands (optional)
  - Check Rust's website for download instructions
  
**Commands which requires package installation have to be runned with administartor/root access!**

### Build & Run - Windows
1. Build `Termi-GUI` project and copy from `Termi-GUI/x64/Debug` `Termi-GUI.dll` file into `Termi-Main/bin/debug/net6.0`.
2. Then copy from `Termi-Commands/x64/Debug` copy `Termi-Commands.dll` file into `Termi-Main/bin/debug/net6.0` folder/directory.
3. Build `Termi-Main` project and run executable

### Build & Run - Other platforms
- Just run `compile_all.sh` (it won't compile test Rust command) script from `Termi-Other` folder or follow steps below:
1. Compile `Termi-Commands` project by running `cmake . && make`
2. Compile `Termi-GUI` project by running `cmake . && make`
3. Copy `libTermi-GUI.so` and `libTermi-Commands.so` files into `Termi-Main` project.
4. Compile `Termi-Main` project by running ```cmake . && make && ./Termi-OpenGL```. If you can't compile project check [this video](hhttps://www.youtube.com/watch?v=CIbJ5Iw0yAs), check description of video just in case there is something important!

### For those who want know more
1. You can compile `rtest` Rust project by `cargo build` (and then copy .dll or .so file in folder/directory where are other .dll or .so files) if you want to have `yes` command mainly written in Rust 

## Known issues
- OpenGL might now open when reading from .txt file, remove `render->Settings(1, 0)` and `render->Settings(2, 0)` to size which you want.
- Dear ImGui might cause segmentation fault on BSD based operating systems **(we are fixing this currently)**.
- Running `Termi-Main` can result: `libTermi-GUI.so: cannot open shared object file: No such file or directory` error; run `Termi-Main` with this command: `LD_LIBRARY_PATH=. ./Termi-Main`

## Development pictures (pictures may be late)
![image](https://user-images.githubusercontent.com/83548580/191842065-6c5fdfec-cd70-49f5-8268-4f7b255796dc.png)
Termi running `sysfetch` command on GNU/Linux, Arch Linux

![image](https://user-images.githubusercontent.com/83548580/191947406-51764cf6-e1c9-420b-8cf5-f5069b975327.png)
Termi running `calc` and `base64` commands on GNU/Linux, Arch Linux

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
- [dl-libraries.html](https://tldp.org/HOWTO/Program-Library-HOWTO/dl-libraries.html) - for loading functions from .so files at runtime
- Other artcicles about programming (web format, books, etc.)

*Word `terminal` might not be the best word to describe this project*
____________________________________

Thank you for choosing Termi.

© 2021 - present ringwormGO
