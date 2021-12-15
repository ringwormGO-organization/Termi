# Termi
Powerful terminal made in C++ and C#

# More about Termi
Termi is powerful terminal made in C++ and C#

It can be run on Windows and Linux.

The goal of Termi is create independent terminal.

"Independent" mean to be independent from terminal in operating system.

We are accept contibutors, create **Pull Request**.

# Checklist

### Termi C++ part
- [x] Windows version
- [x] Linux version
- [ ] macOS version

### Windows - installer and launcher

- [x] Setup in [Inno Setup](https://github.com/jrsoftware/issrc)
- [x] Lanucher and updater - C#

### Other

- [ ] Independence

# Build & Run

### Software you need:

- Visual Studio 2019 with ```.NET desktop development``` and ```Desktop development with C++``` components - Windows version
- G++ complier - Linux version, install with: ```sudo apt-get install g++```

### Build & Run - Windows version
Open two Visual Studio Solutions, compile Termi project as .dll and compile & run Termi-Runner-Console as .exe

If you want run Termi, install [.NET SDK 5.0](https://dotnet.microsoft.com/en-us/download/dotnet/5.0) and run [Termi Installer](https://github.com/ringwormGO-organization/Termi/blob/main/Termi-Windows/Installer/Termi-Installer.exe). This option is recommended for stable releases of Termi

### Build & Run - Linux version
Type this in terminal:

```g++ -o Termi Termi.cpp```
____________________________________

Thanks for choosing Termi

© 2021 ringwormGO
