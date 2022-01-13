# Termi
A Powerful Terminal made in C++ and C#

## About Termi
- Termi is a powerful terminal made in C++ and C#
- It can run on Windows and Linux.
- The goal of Termi is create independent terminal.
- `Independent` mean to be independent from terminal in operating system i.e. a separate kind of terminal.
- We accept contibutors, create a **Pull Request** to contribute.

## TO DO

### Termi C++ part
- [x] Windows version
- [x] Linux version
- [x] macOS version (same folder/directory as Linux version)

### Windows - installer and launcher

- [x] Setup in [Inno Setup](https://github.com/jrsoftware/issrc)
- [x] Lanucher and updater - C#

### Independence
- [ ] Independence
- [ ] Independence - OpenGL

## Build & Run

### Required software:

- Visual Studio 2019 with `.NET desktop development` and `Desktop development with C++` components - Windows.
- G++ complier - Linux version
  - Install with ```sudo apt install g++``` if not already installed.

### Build & Run - Windows
- Open two Visual Studio Solutions, compile `Termi project` as a `.dll` and compile & run `Termi-Runner-Console` as an executable (`.exe`).
- If you want run Termi, install [.NET SDK 5.0](https://dotnet.microsoft.com/en-us/download/dotnet/5.0) or above and run [Termi Installer](https://github.com/ringwormGO-organization/Termi/blob/main/Termi-Windows/Installer/Termi-Installer.exe). This option is **recommended** for stable releases of Termi.

### Build & Run - Linux version & MacOS version (unsupported)
Compile `Termi.cpp`:

```sh
$ g++ -o Termi Termi.cpp
```
____________________________________

Thanks for choosing Termi.

© 2021 ringwormGO
