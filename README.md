# Termi
A powerful terminal emulator with an optional custom shell written in C++ with OpenGL and Dear ImGui.

The goal is to create an independent terminal environment which is still able to access other environments.

## About Termi
- Termi is a powerful terminal emulator with a shell written in C++.
- It can run on Windows, (macOS), (GNU/)Linux, BSD and all other platforms which support used technologies.
- The goal of Termi is to create an independent terminal environment, i.e. a separate kind of terminal emulator which uses "own" rendering and shell system.
- Has two distinct running modes:
  - `simple console mode` - can only execute commands from dynamic libraries that are designed to support Termi,
  - `advanced console mode` - can execute anything as any other terminal emulator.
- Read [CONTRIBUTING.md](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md) and [CODE.md](https://github.com/ringwormGO-organization/Termi/blob/main/CODE.md) for more information.

## Releases
- [v1.0.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v1.0.0)
- [v2.0.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v2.0.0)
- [v3.0.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v3.0.0)
- [v3.1.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v3.1.0)
- [v3.1.1](https://github.com/ringwormGO-organization/Termi/releases/tag/v3.1.1)
- [v3.2.0](https://github.com/ringwormGO-organization/Termi/releases/tag/v3.2.0)
- [Latest release (v3.3.0)](https://github.com/ringwormGO-organization/Termi/releases/tag/v3.3.0)

## Build & Run
### Required software:
### Windows
- Visual Studio Visual Studio 2022 with ```Desktop development with C++```, and ```.NET 6 Runtime``` components.
- vcpkg

### Other platforms
- C++ compiler: GCC and Clang are both supported (they are compatible)
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
  - Install it using vcpkg using on Windows (static x64) (`vcpkg install json-c:x64-windows-static`)
  - Use your package manager, or [download it](github.com/json-c/json-c)

- OpenGL & its dependencies
  - ### Windows
    #### Generating files
    1. Download [GLFW](https://www.glfw.org/),
    2. go to https://glad.dav1d.de/,
    3. generate glad with following properties:
          - `gl`: Version 3.3,
          - `Profile`: Core;
    4. download generated `glad.zip`,
    5. extract zip archives,
    6. open `cmake-gui` program and set following parameters:
          - `Where is the source code`: /path-to-extracted-glfw-folder,
          - `Where to build binaries`: /path-to-extracted-glfw-folder/build,
          - click `Configure`,
          - select `GLFW_BUILD_DOCS`, `GLFW_BUILD_EXAMPLES`, `GLFW_BUILD_TESTS`, `GLFW_INSTALL` and `GLFW_MSVC_RUNTIME_LIBRARY_DLL`,
          - click `Generate`,
          - enter `/path-to-extracted-glfw-folder/build`, open a solution in Visual Studio and build the solution;
    7. in `Termi-GUI` folder create `Libraries` folder with `include` and `lib` subfolders,
    8. copy `glfw3.lib` found in `/path-to-extracted-glfw-folder/build/src/Debug` to `Termi-GUI/Libraries/lib`,
    9. copy `GLFW` folder found in `/path-to-extracted-glfw-folder/include` to `Termi-GUI/Libraries/include`,
    10. copy `glad` and `KHR` folders found in `/path-to-extracted-glad-folder/include` to `Termi-GUI/Libraries/include`;
    11. check [this](https://www.youtube.com/watch?v=XpBGwZNyUh0) video if you are stuck.

    #### Continuing with installation
    - Configure `Termi-GUI` solution:
      1. open properties of `Termi-GUI` **project**,
      2. go to `VC++ Directories`,
      3. set path of `Include Directories` to `Libraries/includes` folder,
      4. set path of `Library Directories` to `Termi-GUI` `Libraries/lib`;
      5. if you get in trouble, check [this](https://www.youtube.com/watch?v=XpBGwZNyUh0) video.
  - ### macOS, (GNU/)Linux & BSD
    #### Generating files
      1. Go to https://glad.dav1d.de/,
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
2. Go to `Termi-Commands` folder/directory, create `build` folder and run `cmake ..` from newly created folder.
3. Open Visual Studio solution and compile it.
4. Repeat steps for other projects.
5. Copy `Termi-Commands.dll` and `Termi-GUI.dll` from `Debug` or `Release` folder to `Termi-Main`'s `Debug` or `Release` folder.
6. Now run `Termi-Main` executable!

**(Developer notes) Don't forget to use `Release` mode, zip it in `windows-release` and update version file so it's available to Termi-Launcher!**

### Build & Run - Other platforms
- Just run `compile_all.sh` (it won't compile test Rust command)
  - first argument is number of threads, by default, we use 2 threads
    for a faster build experience.
  - second argument is do you want clean build, if you do, specify clean
  - example: `./compile_all.sh 4 clean`

### For those who want know more
1. You can compile `rtest` Rust project by `cargo build` (and then copy .dll or .so file in folder/directory where are other .dll or .so files) if you want to have `yes` command mainly written in Rust 

## Known issues
- Dear ImGui might cause segmentation fault on BSD based operating systems **(we are fixing this currently)**.
- Running `Termi-Main` can result in: `libTermi-GUI.so: cannot open shared object file: No such file or directory` error; run `Termi-Main` with this command: `LD_LIBRARY_PATH=. ./Termi-Main`.
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
