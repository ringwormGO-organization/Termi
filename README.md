# Termi
**If you want use non-OpenGL version, manually install files from commits history!**

**Syncing Windows version may not be regular!**

**[Latest stable release (v3.0.0)](https://github.com/ringwormGO-organization/Termi/releases/tag/v3.0.0)**

A Powerful terminal made in C++ with OpenGL and Dear ImGui with own commands

## About Termi
- Termi is a powerful terminal written in C++.
- It can run on Windows, (macOS) and GNU/Linux, BSD and all other platforms which support C++ standard library, something like .dll and .so files and GLFW
- The goal of Termi is create independent terminal, i.e. a separate kind of terminal use "own" GUI renedering system.
- Has own commands that can be written using C, C++ or Rust and possibly any language that can be compiled in form of shared library.
- We accept contributors; create a **Pull Request** to contribute and check [our coding style](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#coding-sytle-for-pull-requests)
- [Commands list and explanation](https://github.com/ringwormGO-organization/Termi/blob/main/Commands.md)
- And plese read [organize part](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#code-organization) which talk about directory organization.

## Releases
- [v1.0.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v1.0.0).
- [v2.0.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v2.0.0)
- [Latest release (v3.0.0)](https://github.com/ringwormGO-organization/Termi/releases/tag/v3.0.0)

## Checklist
### Termi base part
- [x] Windows version (moderately supported)
- [x] GNU/Linux version (fully supported)
- [x] BSD version (moderately supported)
- [x] macOS version (unsupported)

### Termi advanced C++ part
- [x] Arguments
- [x] Better arguments for Rust commands/applications
- [x] Colors in console
- [x] GUI models (actually do something with model 1)
- [x] Loading executables (.dll files for Windows, .so files for macOS, GNU/Linux, BSD, etc.)
- [x] Most of major commands
- [x] Networking
  - [x] [Ping command](https://github.com/ringwormGO-organization/Ping) - [@StjepanBM1](https://github.com/StjepanBM1)
  - [ ] Remote connection
- [ ] Serial port
- [x] Themes
- [x] Translations
- [x] User settings in JSON
- [x] [UTF-8 support](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#glyph-range-utf-8-support)

### Windows - installer and launcher
- [x] Installer in [Inno Setup](https://github.com/jrsoftware/issrc)
- [x] Lanucher and updater - C#

## Build & Run
### Required software:
### Windows
- Visual Studio Visual Studio 2022 with ```Desktop development with C++```, and ```.NET 6 Runtime``` components.
- vcpkg

### Other platforms
- g++ complier
  - Install with ```apt-get install gcc g++``` if not already installed on GNU/Linux machine, Debian based.
  - Install with ```pacman -S gcc g++``` if not already installed on GNU/Linux machine, Arch based.
- build-essential
  - Install with ```apt-get install build-essential``` if not already installed on GNU/Linux machine, Debian based.
  - Install with ```pacman -S base-devel``` if not already installed on GNU/Linux machine, Arch based.

### All platfoms
- Git - for cloning repo
  - Check Git website for Windows instructions or do `winget install git`
  - Install with ```apt-get install git``` if not already installed on GNU/Linux machine, Debian based.
  - Install with ```pacman -S git``` if not already installed on GNU/Linux machine, Arch based.
- CMake
  - Install with ```apt-get install cmake``` if not already installed on GNU/Linux machine, Debian based.
  - Install with ```pacman -S cmake``` if not already installed on GNU/Linux machine, Arch based.
- json-c library (non-vcpkg version)
  - Install it using vcpkg using on Windows (static x64)
  - Install with `apt-get install libjson-c-dev` if not already installed on GNU/Linux machine, Debian based.
  - Install with `pacman -S json-c` if not already installed on GNU/Linux machine, Arch based.

- OpenGL & its dependencies
  - ### Windows
    #### Generating files (optional)
    - Check [this](https://www.youtube.com/watch?v=XpBGwZNyUh0) video and copy new files where old ones are.

    #### Using a files
    - Visual Studio 2022 solution should work without any additional configuration.
    - If it doesn't work, see following instructions down below:
      1. open properties of solution,
      2. go to `VC++ Directories`,
      3. set path of `Include Directories` to `includes` folder,
      4. set path of `Library Directories` to `Termi-GUI` folder where `glfw3.lib` is located;
      5. if you get in trouble, check [this](https://www.youtube.com/watch?v=XpBGwZNyUh0) video.
  - ### macOS & (GNU/)Linux
    #### Generating files (optional)
      1. go to https://glad.dav1d.de/,
      2. generate glad with following properties:
          - `gl`: Version 3.3,
          - `Profile`: Core;
      3. download generated `glad.zip`,
      4. extract `glad.zip`,
      5. copy `/include/glad` folder to `/usr/include`,
      6. install `glfw` package;

      - if you get in trouble, check [this](https://www.youtube.com/watch?v=CIbJ5Iw0yAs) video.

  - ### BSD
    - Steps are same as for (GNU/Linux), but:
      - copy `GLFW` to `/usr/local/lib`,
      - copy `gl.h` to `/usr/X11R6/lib`.

  *NOTE: There is option in `Settings.hpp` to use headers in this repository*

- Rust - required for building Rust commands (optional)
  - Check Rust's website for download instructions
  
**Commands which requires package installation have to be ran with administrator/root access!**

### Build & Run - Windows
1. Open `Developer Powershell for Visual Studio 2022`
2. Go to `Termi-Commands` folder/directory and run this command: `clear | cmake . | nmake`
3. Go to `Termi-GUI` folder/directory, make `build` folder/directory, enter it and run `cmake ..`, but before that set a path where is `json-c` installed using `vcpkg` in `CMakeLists.txt` and copy `glfw3.lib` in `build` folder/directory from `Termi-GUI` folder/directory
4. Go to `build` folder/directory, open Visual Studio solution and compile `ALL_BUILD` project
5. Go to `Termi-Main` folder and run this command: `clear | mkdir build | cd build | cmake ..`
6. Go to `build` folder/directory, open Visual Studio solution and compile `ALL_BUILD` project
7. Now copy all DLLs to `Debug` folder/directory where is `Termi-Main` executable for Windows located
8. Now run `Termi-Main` executable!

**Don't forget to use `Release` mode!**

### Build & Run - Other platforms
- Just run `compile_all.sh` (it won't compile test Rust command)
1. Compile `Termi-Commands` project by running `cmake . && make`
2. Compile `Termi-GUI` project by running `cmake . && make`
3. Copy `libTermi-GUI.so` and `libTermi-Commands.so` files into `Termi-Main` folder/directory.
4. Compile `Termi-Main` project by running ```cmake . && make && ./Termi-OpenGL```.

### For those who want know more
1. You can compile `rtest` Rust project by `cargo build` (and then copy .dll or .so file in folder/directory where are other .dll or .so files) if you want to have `yes` command mainly written in Rust 

## Known issues
- OpenGL might now open when reading from .txt file, remove `render->Settings(1, 0)` and `render->Settings(2, 0)` to size which you want.
- Dear ImGui might cause segmentation fault on BSD based operating systems **(we are fixing this currently)**.
- Running `Termi-Main` can result: `libTermi-GUI.so: cannot open shared object file: No such file or directory` error; run `Termi-Main` with this command: `LD_LIBRARY_PATH=. ./Termi-Main`.
- `cd` command disables autofocus on input bar.
- You have to press button for other themes (not light/dark) to be able to switch between light and dark themes.

## Development pictures (pictures may be late)
![image](https://user-images.githubusercontent.com/83548580/191842065-6c5fdfec-cd70-49f5-8268-4f7b255796dc.png)
Termi running `sysfetch` command on GNU/Linux, Arch Linux

![image](https://user-images.githubusercontent.com/83548580/191947406-51764cf6-e1c9-420b-8cf5-f5069b975327.png)
Termi running `calc` and `base64` commands on GNU/Linux, Arch Linux

## External dependencies
- [OpenGL](https://www.opengl.org/)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [stb](https://github.com/nothings/stb)
- [Sweet16Font](https://github.com/kmar/Sweet16Font)
- [dirent](https://github.com/tronkko/dirent) - ```dirent.h``` for Windows

## Credits
- [Background launcher picture](https://pixabay.com/photos/leaf-maple-autumn-foliage-botany-3865014/)
- [Stack Overflow](https://stackoverflow.com/) - solution for most of problems
- [Cherno](https://www.youtube.com/c/TheChernoProject) - for recommending Dear ImGui
- [Victor Gordan](https://www.youtube.com/c/VictorGordan) - for OpenGL window code
- [cppfetch](https://github.com/Phate6660/cppfetch) - for Termi's `sysfetch`
- [dl-libraries.html](https://tldp.org/HOWTO/Program-Library-HOWTO/dl-libraries.html) - for loading functions from .so files at runtime
- [c-chatroom](https://github.com/lovenery/c-chatroom) - for server & client implementation
- ...

*Word `terminal` might not be the best word to describe this project*

*[GitLab mirror](https://gitlab.com/ringwormgo/Termi)*
____________________________________

Thank you for choosing Termi.

© 2021 - present ringwormGO
