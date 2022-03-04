# Termi
(Termi currently is just a terminal app but we are developing it to be a fully working terminal not just an app)

A Powerful Terminal made in C++ and C#

## About Termi
- Termi is a powerful terminal made in C++ and C#
- It can run on Windows, macOS and GNU/Linux.
- The goal of Termi is create independent terminal.
- `Independent` mean to be independent from terminal in operating system i.e. a separate kind of terminal use "own" GUI renedering.
- We accept contibutors, create a **Pull Request** to contribute and check [our coding style](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#coding-sytle-for-pull-requests)
- And plese read [organize part](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#code-organization) which talk about directory organization.

## Checklist


### Termi base C++ part
- [x] Windows version
- [x] Linux version
- [x] macOS version (same folder/directory as GNU/Linux version)

### Termi C++ part
- [ ] User settings in JSON
- [ ] Support all major commands
- [ ] Include other host terminals

### Windows - installer and launcher
- [x] Setup in [Inno Setup](https://github.com/jrsoftware/issrc)
- [x] Lanucher and updater - C#

### Independence
- [ ] Independence ([ImGUI](https://github.com/ocornut/imgui))

## Build & Run
### Required software:
- Visual Studio 2019 or Visual Studio 2022 with `.NET desktop development` (if you use Visual Studio 2022, add .NET 5 runtime too) and `Desktop development with C++` components - Windows.
- G++ complier - GNU/Linux
  - Install with ```sudo apt install g++``` if not already installed.

### Build & Run - Windows
- Open `Developer Command Prompt for VS 2019` or `Developer Command Prompt for VS 2022` and run `compile.bat`.
- Open Termi Visual Studio Solution and compile it.
- If you want run Termi as standard user, check latest release and download executable. When you launching installed app, run application as **ADMINISTRATOR**.

### Build & Run - GNU/Linux version (& macOS version which unsupported)
Run `.build.sh`:

```sh
$ chmod +x ./build.sh && ./build.sh
```

### Build & Run - Package Manager
- Enter proper directory and choose command to compile.
#### Windows (MSVC compiler)
Open `Developer Command Prompt for VS 2019` or `Developer Command Prompt for VS 2022` and paste command.

```
cl /EHsc PackageManager.cpp
```

#### Linux (G++ compiler)
Open terminal and paste command
```sh
$ g++ -o PackageManager PackageManager.cpp
```

## Credits
- [Background launcher picture](https://pixabay.com/photos/leaf-maple-autumn-foliage-botany-3865014/)
____________________________________

Thank you for choosing Termi.

© 2022 ringwormGO
