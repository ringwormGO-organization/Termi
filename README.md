# Termi
A powerful terminal emulator with an optional custom shell written in C++ with OpenGL and Dear ImGui

## About Termi
- Termi is a powerful terminal emulator with a shell written in C++.
- It can run on Windows, (macOS) and GNU/Linux, BSD and all other platforms which support C++ standard library, something like .dll and .so files and GLFW
- The goal of Termi is to create independent terminal emulator, i.e. a separate kind of terminal emulator use "own" GUI renedering system.
- Has its own commands that can be written using C, C++ or Rust and possibly any language that can be compiled in form of shared library.
- We accept contributors; create a **Pull Request** to contribute and check [our coding style](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#coding-sytle-for-pull-requests)
- [Commands list and explanation](https://github.com/ringwormGO-organization/Termi/blob/main/Commands.md)
- And please read [organize part](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#code-organization) which talks about directory organization.

## Releases
- [v1.0.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v1.0.0).
- [v2.0.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v2.0.0)
- [v3.0.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v3.0.0)
- [v3.1.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v3.1.0)
- [Latest release (v3.1.1)](https://github.com/ringwormGO-organization/Termi/releases/tag/v3.1.1)

## Checklist
### Termi base part
- [x] Windows version (fully supported with delays)
- [x] GNU/Linux version (fully supported)
- [x] BSD version (moderately supported) [(@hahahahacker2009)](https://github.com/hahahahacker2009)
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
  - [x] Remote connection
- [ ] Serial port
- [x] Themes
- [x] Translations
- [x] User settings in JSON
- [x] [UTF-8 support](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#glyph-range-utf-8-support)

### Windows - installer and launcher
- [x] Installer in [Inno Setup](https://github.com/jrsoftware/issrc)
- [x] Launcher and updater - C#

## Build & Run
### Required software:
### Windows
- Visual Studio Visual Studio 2022 with ```Desktop development with C++```, and ```.NET 6 Runtime``` components.
- vcpkg

### Other platforms
- C++ complier: GCC and Clang are both supported (they are compatible)
- C & C++ headers: you should have them by default. If not, you can try
  installing what's called base-devel or build-essentials or build-base.
  Strictly speaking, they are a collection of tools required to build the
  whose Linux distribution, including kernel.
  Linux packaging often split package into binary components and header, the
  header usually contain the postfix -dev or -devel
On BSD, you can get all of them with the "compiler" sets.

### All platfoms
- (Optional) Git - for cloning repo
  - Check Git website for Windows instructions or do `winget install git`
  - Use your package manager or [get the software from the official website](git-scm.com/download).

- CMake
  - Visual Studio have option for installing cmake
  - Use your package manager or [get the software at their official website](cmake.org/download/).

- json-c library header (non-vcpkg version)
  - Install it using vcpkg using on Windows (static x64)
  - Use your package manager, or [download it](github.com/json-c/json-c)

- OpenGL & its dependencies
  - ### Windows
    #### Generating files (optional)
    - Check [this](https://www.youtube.com/watch?v=XpBGwZNyUh0) video and copy new files where old ones are.

    #### Continuing with installation
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
      5. copy `./include/glad` folder to `/usr/include` (Linux), or `/usr/local/include`
         (or even /usr/pkg/include), (for BSD and maybe macOS).

    #### Continuing with installation
      1. install `glfw` package: both the shared object and the header;
         You can use your package manager.
      2. if you get in trouble, check [this](https://www.youtube.com/watch?v=CIbJ5Iw0yAs) video.
      - (Developer notes) Linux (package managers) do not use the /usr/local
        hierarchy, while BSD do, for "third-party software".
        NetBSD use the /usr/pkg hierarchy instead of /usr/local;
        OpenBSD and NetBSD have X by default, so they use /usr/X11R6 and
        /usr/X11R7 hierarchy to store X file, whereas on FreeBSD X is
        third-party software so it is installed on /usr/local .
        The compilation flags for each system is all added, no need to worry
        here.

- Rust - required for building Rust commands (optional)
  - Check Rust's website for download instructions
  
**Commands which requires package installation have to be ran with administrator/root access!**

### Build & Run - Windows
1. Open terminal.
2. Go to `Termi-Commands` folder/directory and run this command: `cmake .` command.
3. Open Visual Studio solution and compile it.
4. Repeat steps for other projects.
5. Copy `Termi-Commands.dll` and `Termi-GUI.dll` from `Debug` or `Release` mode to `Debug` or `Release` folder where `Termi-Main` is located.
6. Now run `Termi-Main` executable!

**Don't forget to use `Release` mode! and zip it in `windows-release` so it's available to Termi-Launcher**

### Build & Run - Other platforms
- Just run `compile_all.sh` (it won't compile test Rust command)
  - first argument is number of threads, by default, we use 2 threads
    for a faster build experience.
  - second argument is do you want clean build, if you do, specify clean
  - example: `./compile_all.sh 4 clean`

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

*[Codeberg mirror](https://codeberg.org/ringwormGO/Termi)*
____________________________________

Thank you for choosing Termi.

© 2021 - present ringwormGO
