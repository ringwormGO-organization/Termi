# How to start contributing
Just drop a Pull Request :)

# Pull Request style
1. Use LF. Set up your Git settings with this: `git config --global core.autocrlf false` and check if it is OK by `git config --global core.autocrlf`. It need to return `false` or nothing.
2. Use CRLF for Windows code, LF for (GNU/)Linux code
3. Use following style **WITH LOGIC**, check labels:
4. Use spaces, size 4

```
[LABEL NAME] Name of Pull Request
```
# Directory organization (OpenGL)
## Windows version
1. `Termi-Main` folder/directory is just C# projects which calls GUI code from `Termi-GUI.dll`.
2. `Termi-GUI` is Visual Studio project for GUI code (calls `Termi-Commands.dll` at runtime).
3. `Termi-Commands` is Visual Studio project for core commands (calls `Termi-GUI.dll` at runtime).

## Other versions
1. GNU/Linux version have own folder while Windows version is in `Termi-Windows` directory.
2. Code is in "root" while header files for commands will be in `Commands` directory.
3. `imgui_main.cpp` contains code about rendering windows and console.
4. `imgui_commands.cpp` contains code for commands`.
5. `imgui_code.hpp` is header file for `imgui_main.cpp` and `imgui_commands.cpp`.

# Add language (not programming language) to Termi
1. Add new `std::vector` to `Translation.hpp` in `Translation` namespace.
2. Follow strings' IDs.
3. Add new language in `ChooseLanguageDialog` function.
4. Add new language in `ChooseLanguage` function.

Example:
```cpp
    /* Translation.hpp */
    static std::vector<std::string> Spanish = {"spanish words"};

    /**
     * Naming convention for IDs fot strings
     * 0: Input
     * 1: Terminal
     * 2: Edit
     * 3: About
     * 4: New Tab
     * 5: New profile
     * 6: Exit
     * 7: Font picker
     * 8: Change theme
     * 9: Change language
     * 10: About Termi
     * 11: About Dear ImGui
    */
```
```cpp
/* imgui_main.cpp */
const char* Renderer::ChooseLanguage(Vars* vars, int id)
{
    /* be careful which word you put `ChooseLanguageDialog` funtion */
    if (vars->language == "spanish")
    {
        return Translation::English.at(id).c_str();
    }

    /* nothing matches */
    return "Unknown word";
}

/* Choose a language using dialog */
void Renderer::ChooseLanguageDialog(Vars* vars, bool *p_open)
{
    ImGui::SetWindowPos(ImVec2(200, 200));
    ImGui::SetWindowSize(ImVec2(500, 500));
    if (!ImGui::Begin("Language dialog", p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Button("Close window")) language_dialog = false;
        ImGui::EndPopup();
    }

    ImGui::Text("Choose language / Odaberi jezik");
    ImGui::Text(" "); /* empty space */

    if (ImGui::Button("spanish")) vars->language = "spanish";
    if (ImGui::Button("X")) language_dialog = false;

    ImGui::End();
}
```

# Add command to Termi
## Windows version
### Core commands
1. Add function name in `Export.h` in `Termi-Commands` Visual Studio project.
2. Add C++ code in `Commands.cpp` in `Termi-Commands` Visual Studio project.
3. `AddLog` will work best with one argument so put everything in one `std::string` and pass it to `AddLog`.
4. See example:
```cpp
extern "C"
{
	__declspec(dllexport) void __cdecl example(const std::vector<std::string>& vect);
}; /* Export.h */

void __cdecl example(const std::vector<std::string>& vect)
{
    int number = 30;
    std::string str = "Number is: " + std::to_string(number) + "\n";
    AddLog(str);
}
```

### Port application
1. Create new Visual Studio DLL project.
2. Copy all stuff to load DLL stuff (`AddLog` function mostly).
3. Copy all `_declspec(dllexport)` stuff (see example for core commands).
4. Replace all other functions for printing to console (like `printf`, `std::cout`, etc.) to `AddLog` function (see example for core commands for informations and warnings).

## Other versions
1. Create new file in `Commands` folder and create main function for command.
2. Put command and function name in `commands` `std::map`, need to return integer based on is function executed correctly.
3. Put main command code in `imgui_commands.cpp`.
4. Function argument is: `std::vector<std::string>& vect`
5. Don't forget for arguments even if it is not needed!

Example:
```cpp
int example(std::vector<std::string>& vect); /* command.hpp */
int example(std::vector<std::string>& vect)
{
    cout << "Example\n";
    return 0;
} /* imgui_commands.cpp */
```

Information about elements in vector:
```cpp
vect[0]; /* name of command */
vect[i]; /* argument while `i` represents order of argument */
```

# Coding sytle for Pull Requests
### Indentation and line width
1. Line width much be at most **100** characters.
2. Use spaces, spaces size **MUST BE** 4!
3. Indent both a case label and the case statement of a switch statement.

Right:

```c
switch (Condition)
{
    case 1:
        DoSomething();
        break;
}
```
Wrong:

```c
switch (Condition)
{
case 1:
     DoSomething();
     break;
}
```
When a function call does not fit onto a line, align arguments like this:

```c
FunctionCall(arg1,
             arg2,
             arg3);
```

When making new functions, use an return type.
Right:
```c
int func() {}
```
Wrong:
```c
func() {}
```

### Spacing
1. Do not use spaces around unary operators.

**Right:** `i++`

**Wrong:** `i ++`

-------------------------------------------------------------

2. Place spaces around binary and ternary operators.

**Right:** `a = b + c;`

**Wrong:** `a=b+c;`

3. Do not place spaces before comma and semicolon.

Right:

```c
for (int i = 0; i < 5; i++)
    DoSomething();

func1(a, b);
```

Wrong:

```c
for (int i = 0 ; i < 5 ; i++)
    DoSomething();
    
func1(a , b) ;
```

4. Place spaces between control statements and their parentheses.

Right:

```c
if (Condition)
    DoSomething();
```

Wrong:

```c
if(Condition)
    DoSomething();
```

5. Do not place spaces between a function and its parentheses, or between a parenthesis and its content.

Right:

`func(a, b);`

Wrong:

```c
func (a, b);
func( a, b );
```

### Line breaking
1. Each statement should get its own line.

Right:

```c
x++;
y++;

if (Condition)
{
    DoSomething();
}
```
Also right but don't use it often

```c
if (Condition) DoSomething(); 

if (Condition)
    DoSomething();
```
Wrong:

```c
x++; y++;
```

### Braces
1. Always put braces ({ and }) on their own lines.
2. One-line control clauses may use braces, but this is not a requirement. An exception are one-line control clauses including additional comments.

Right:

```c
if (Condition)
    DoSomething();

if (Condition)
{
    DoSomething();
}

if (Condition)
{
    // This is a comment
    DoSomething();
}


if (Condition)
    DoSomething();
else
    DoSomethingElse();

if (Condition)
{
    DoSomething();
}
else
{
    DoSomethingElse();
    YetAnother();
}
```

Wrong:

```c
if (Condition) {
    DoSomething();
}

if (Condition)
    // This is a comment
    DoSomething();

if (Condition)
    DoSomething();
else
{
    DoSomethingElse();
    YetAnother();
}
```

### Control structures
1. Don’t use inverse logic in control clauses.

**Right:** `if (i == 1)`
**Wrong:** `if (1 == i)`

2. Avoid too many levels of cascaded control structures. Prefer a “linear style” over a “tree style”. Use goto when it helps to make the code cleaner (e.g. for cleanup paths).

Right:

```c
if (!func1())
    return;

i = func2();
if (i == 0)
    return;

j = func3();
if (j == 1)
    return;
```
…

Wrong:

```c
if (func1())
{
    i = func2();
    if (func2())
    {
        j = func3();
        if (func3())
        {
            …
        }
    }
}
```

### Naming
*Part called "Naming" is wrote by ringwormGO itself*

#### Naming functions
1. Name a function by capital letter.

**Right:** `void Test();`

**Wrong:** `void test();`

#### Naming structs, classes, unions and variables
2. Name a struct, class, union etc. with cappital letter and variable which lowercase letter

**Right:**
```c
struct Test
{
  int number;
}

Test test;
```

**Wrong:**
```c
struct test
{
  int Number;
}

test Test;
```

### Commenting
1. Avoid line-wasting comments, which could fit into a single line.

Right:

```c
// This is a one-line comment

/* This is a C-style comment */


//
// This is a comment over multiple lines.
// We don’t define any strict rules for it.
//
```

Wrong:

```c
//
// This comment wastes two lines
//
```

### Null, false and 0
1. The null pointer should be written as NULL.
2. In the rare case that your environment recommends a different null pointer (e.g. C++11 nullptr), you may use this one of course. Just don’t use the value 0.

### Notes on reformatting existing code
1. Never totally reformat a file and put a code change into it. Do this in separate commits.
2. If a commit only consists of formatting changes, say this clearly in the commit message by preceding it with [FORMATTING].

### Other points
1. Do not use `LARGE_INTEGER`/`ULARGE_INTEGER` unless needed for using APIs. Use `int64`/`uint64` instead
2. Use `#pragma once` instead of guard defines in headers
3. Don't specify a calling convention for a function unless required (usually for APIs or exported symbols)

### Resources used for this coding style:
* https://reactos.org/wiki/Coding_Style (some parts are modificeted)
