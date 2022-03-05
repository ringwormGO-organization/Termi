# Termi
(Termi currently is just a terminal app but we are developing it to be a fully working terminal not just an app)

A Powerful Terminal made in C++

## About Termi
- Termi is a powerful terminal made using C++.
- It can run on Windows, macOS and GNU/Linux.
- The goal of Termi is create independent terminal.
- `Independent` mean to be independent from terminal in operating system i.e. a separate kind of terminal use "own" GUI renedering system.
- We accept contibutors, create a **Pull Request** to contribute and check [our coding style](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#coding-sytle-for-pull-requests)
- And plese read [organize part](https://github.com/ringwormGO-organization/Termi/blob/main/CONTRIBUTING.md#code-organization) which talk about directory organization.

## Checklist
### Termi base C++ part
- [x] Windows version
- [x] GNU/Linux version
- [x] macOS version (same folder/directory as GNU/Linux version)

### Termi C++ part
- [ ] User settings in JSON
- [ ] Support all major commands
- [ ] Include other host terminals

### Independence
- [ ] Independence ([ImGUI](https://github.com/ocornut/imgui))

## Build & Run
### Required software:
- Visual Studio 2019 or Visual Studio 2022 and `Desktop development with C++` components (if you use Visual Studio 2019, add support for Visual Studio 2019) - Windows.
- G++ complier - GNU/Linux
  - Install with ```sudo apt install g++``` if not already installed.
- Git
  - Install with ```sudo apt-get install git``` if not already installed on Linux machine.

### Build & Run - Windows
- Open `Developer Command Prompt for VS 2019` or `Developer Command Prompt for VS 2022` and run `compile.bat`.
- Open Termi Visual Studio Solution and compile it.
- If you want run Termi as standard user, check latest release and download executable or simply clone repo and update it with `git pull`. When you launching installed app, run application as **ADMINISTRATOR**.
- If you run application from Visual Studio, loading executables won't work because running from `Debug` folder/directory isn't same as running from Visual Studio!

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
- Stack Overflow
____________________________________

Thank you for choosing Termi.

© 2022 ringwormGO
