# List of Termi's commands and their explanation and arguments sorted in alphabetical order

All arguments are `std::string` type, Termi will convert it later if needed;

List of arguments in "C++ style":
 - `vect[i]` = argument, `i` represents order

**When typing arguments, don't use brackets and commas!**

```c
string encode = "-e";
string decode = "-d";
base64((do_encode == 1) ? encode : decode, text);
/* 
    Encodes plain text or decoding base64 text and printing result to 
    console
*/
```

```c
calc(operator, num1, num2);
/* 
    Based on operator (+, -, *, /) Termi will perform an math operation and print result to console.
*/
```

```c
cd(directory)
/*
    Enters directory by passed argument
*/
```

```c
dencalc(mass, volume, density);
/*
    mass - grams
    volume - cm3
    density - g/cm3

    Use x if that value requires calculation
*/
```

```c
echo(text, text2);
/*
    Prints to console all passed arguments
*/
```

```c
find(path, file);
/*
    Searches file or directory in folder/directory.
*/
```

```c
geocalc(std::vector<std::string>& vect);
/*
    Perform geo calculations and Termi 
    will print output to console

    SUR = surface
    EXT = extent

    REC = rectangle
    SQU = square
    TRI = triangle

    OPTIONS:
        1. vect[1] == "SUR"
            1. vect[2] == "REC"
                1. x = vect[3]
                2. y = vect[4]

            2. vect[2] == "SQU"
                1. x = vect[3]

            3. vect[2] == "TRA"
                1. x = vect[3]
                2. Vx = vect[4]

        2. vect[1] == "EXT"
            1. vect[2] == "TRA"
                1. x = vect[3]
                2. y = vect[4]
                3. z = vect[5]

            2. vect[2] == "REC"
                1. x = vect[3]
                2. y = vect[4]

            3. vect[2] == "SQU"
                1. x = vect[3]
*/
```

```c
list(folder)
/* 
    List all files and directories in folder/directory.
*/
```

```c
loadtp(path, function_name, value)
/* 
    Calls third party command or application.
    path - path of .dll or .so file
    function_name - name of function to be called
    value - argument, more arguments can be passed but they will be combined in one string
*/
```

```c
mkdir(name)
/* 
    Creates new folder/directory which given name.
*/
```

```c
openfile(file)
/* 
    Displays all content from file line by line.
*/
```

```c
rm(file)
/* 
    Removes file which given name.
*/
```

```c
sysfetch()
/* 
    Displays computer informations, all passed arguments will be ignored.
*/
```


```c
time()
/* 
    Displays time, all passed arguments will be ignored.
*/
```


```c
whoami()
/* 
    Displays current logged user, all passed arguments will be ignored.
*/
```

```c
writefile(file, content)
/* 
    Writes given content to given file.
*/
```

```c
yes()
/* 
    Displays word `yes` 100000, all passed arguments will be ignored.
    This function can slow down Termi
*/
```

Thank you for choosing Termi.

© 2022 ringwormGO
