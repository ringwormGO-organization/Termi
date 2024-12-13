# CODE.md

This document explains Termi's code and relevant things when using it.

# Directory organization

1. `Termi-Commands` folder/directory - core commands
2. `Termi-GUI` folder/directory - GUI
3. `Termi-Main` folder/directory - call GUI

# Add translation to Termi

1. Add language name in English in `language_id` vector in `translation.hpp`.
2. **Don't forget to capitalize its name and sort it alphabetically, but keep English first!**
3. Add translated text to vector in map \*\*making sure it's aligned as in `language_id` vector.
4. Add button to change language in `ChooseLanguageDialog` dialog in `imgui.cpp`:

```cpp
if (ImGui::Button("English name / Native name") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
{
    vrenderer[vrenderer_id]->language = "English name";
}
```

# Glyph range (UTF-8 support)

- `default` - Basic Latin + Latin Supplement
- `korean`
- `chinese_full`
- `chinese_simplified_common`
- `japanese`
- `cyrillic`
- `thai`
- `vietnamese`
- `latin-ex-a`- Basic Latin + Latin supplement + Latin extended A; only usable with `Sweet16.tff` located in `font` folder/directory accessible to `Termi-Main` executable

# Simple console mode

## Add core command to Termi

1. Add function name in `Export.h` in `Termi-Commands` project.
2. Add C++ code in `Commands.cpp` in `Termi-Commands` project.
3. See example:

```cpp
extern "C"
{
	EXPORT example(const std::vector<std::string>& vect);
}; /* Export.h */

VOID example(const std::vector<std::string>& vect)
{
    /* AddLog is "printf" function of console */
    /* Call Status() function at the end */

    int number = 30;
    AddLog("Number is: %d\n", number);

    Status(0);
} /* Commands.cpp */
```

## Port application

### Windows

1. Create new Visual Studio DLL project.
2. Copy `AddLog` and `LoadDynamicLibrary` functions.

```cpp
    #pragma warning(disable: 4996)
    #pragma comment(lib, "Advapi32.lib")
    #pragma comment(lib, "Kernel32.lib")

    template <typename T>
    int LoadDynamicLibrary(const char* path, const char* function, T argument)
    {
        typedef int(__cdecl* MYPROC)(T);

        HINSTANCE hinstLib;
        MYPROC ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        // Get a handle to the DLL module
        hinstLib = LoadLibrary(LPCSTR(path));

        // If the handle is valid, try to get the function address.
        if (hinstLib != NULL)
        {
            ProcAdd = (MYPROC)GetProcAddress(hinstLib, function);

            // If the function address is valid, call the function.
            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(argument);
            }

            else
            {
                printf("Error loading function '%s' from '%s'!\n", function, path);
                return 1;
            }

            // Free the DLL module.
            fFreeResult = FreeLibrary(hinstLib);
        }

        // If unable to call the DLL function, use an alternative.
        if (!fRunTimeLinkSuccess)
        {
            printf("Error loading function '%s' from '%s'!\n", function, path);
            return 1;
        }

        return 0;
    }

    // Explicitly instantiate a template if `LoadDynamicLibrary()` function has to be called from extern "C" block
    template int LoadDynamicLibrary<const char*>(const char* path, const char* function, const char* argument);

    void AddLog(std::string fmt, ...)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt.c_str(), args);
        buf[sizeof(buf) - 1] = 0;
        va_end(args);

        LoadDynamicLibrary("/path/", "AddLog", buf);
    }
```

3. Mark function to be called from program as `_declspec(dllexport)` stuff inside `extern "C"` in .h file and as `void __cdecl` in .cpp file

```cpp
    extern "C"
    {
        __declspec(dllexport) void __cdecl program(const char* arguments);
    }; /* .h file */

    void __cdecl program(const char* arguments); /* .cpp file */
```

4. Replace all other functions for printing to console (like `printf`, `std::cout`, etc.) to `AddLog` function. `AddLog` works like `printf`.
5. Compile and use Termi's `loadtp` command to test it!

### Other platforms

1. Create new project with `CMakeLists.txt` file similar to `Termi-Commands` project
2. Copy `AddLog` and `LoadDynamicLibrary` functions.

```cpp
    template <typename T>
    int LoadDynamicLibrary(const char* path, const char* function, T argument)
    {
        void *handle;
        void (*func)(T);
        char *error;

        handle = dlopen(path, RTLD_LAZY);
        if (!handle)
        {
            fputs (dlerror(), stderr);
            puts(" ");

            return 1;
        }

        func = reinterpret_cast<void (*)(T)>(dlsym(handle, function));
        if ((error = dlerror()) != NULL)
        {
            fputs(error, stderr);
            return 1;
        }

        (*func)(argument);
        dlclose(handle);

        return 0;
    }

    // This explicit template instantiation is making `LoadDynamicLibrary` function available from extern "C" block
    template int LoadDynamicLibrary<const char*>(const char* path, const char* function, const char* argument);

    void AddLog(std::string fmt, ...)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt.c_str(), args);
        buf[sizeof(buf) - 1] = 0;
        va_end(args);

        LoadDynamicLibrary("/path/", "AddLog", buf);
    }
```

3. Put public function inside `extern "C"` in .h file.

```cpp
    extern "C"
    {
        void program(const char* arguments);
    }; /* .h file */

    void program(const char* arguments); /* .cpp file */
```

4. Replace all other functions for printing to console (like `printf`, `std::cout`, etc.) to `AddLog` function. `AddLog` works like `printf`.
5. Compile and use Termi's `loadtp` command to test it!

_Passed argument to a third party commands/applications using `loadtp` command is one combined string. Do parsing inside your command/application, arguments are separated by space!_

## For those who want to know more

### Port application written in Rust

1. Create new Rust library by using cargo - `cargo new --lib name`.
2. Change `Cargo.toml` content to (change `name` and `version`):

```c
[package]
name = "your package name"
version = "version"
edition = "2021"

[lib]
crate-type = ["cdylib"]

[dependencies]
libloading = "0.7"
```

3. Change `lib.rs` content to (change path to .dll or .so file):

```rs
#![allow(non_snake_case)]

use libloading::{Library, Symbol};

use std::ffi::{CStr, CString};
use std::os::raw::c_char;

/// `printf()` for Termi's console
fn AddLog(fmt: &CStr) {
    unsafe {
        let lib = Library::new("path do .dll or .so file").unwrap();
        let foo = lib
            .get::<Symbol<extern "C" fn(*const c_char)>>(b"AddLog")
            .unwrap();

        foo(fmt.as_ptr());
    }
}

/// Separate string into arguments intended for this Rust program
///
/// Returns vector of `CString`
fn GetArguments(arg: *const c_char) -> Vec<CString> {
    let mut vec = Vec::new();

    let arg_buf = unsafe { CStr::from_ptr(arg) };
    let arg_str = arg_buf.to_str().unwrap();

    for word in arg_str.split(' ') {
        let c_string = CString::new(word).expect("Failed to create CString");
        vec.push(c_string);
    }

    return vec;
}

#[no_mangle]
pub extern "C" fn rust_function(arg: *const c_char) {
    /* your code */

    let text = CString::new("Example how to print text to Termi's console from Rust").expect("CString::new failed!");
    AddLog(&text);
}

```

### Informations about elements in vector:

```cpp
vect[0]; /* name of command */
vect[i]; /* argument while `i` represents order of argument */
```

# Advanced Console Mode

In development.
