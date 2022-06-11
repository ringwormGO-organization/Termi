'''
AUTHOR:      Andrej Bartulin
PROJECT:     Termi's Windows version generator
LICENSE:     ringwormGO General License 1.0 | (RGL) 2022
DESCRIPTION: Main file for generator
'''

import os
from os.path import exists
import sys
import shutil

class Utils:
    def remove(path : str, text : str):
        with open(path, "r+") as f:
            d = f.readlines()
            f.seek(0)
            for i in d:
                if i != text:
                    f.write(i)
            f.truncate()

    def replace_chunck(read_path : str, write_path : str, starter_text : str, new_text : str):
        # Read in the file
        with open(read_path, 'r') as file :
            filedata = file.read()

        # Replace the target string
        filedata = filedata.replace(starter_text, new_text)

        # Write the file out again
        with open(write_path, 'w') as file:
            file.write(filedata)

    def add(index : int, path : str, text : str):
        with open(path, "r") as f:
            contents = f.readlines()

        contents.insert(index, text)

        with open(path, "w") as f:
            contents = "".join(contents)
            f.write(contents)

def generate_main(path : str) -> int:
    try:
        if exists("wmain.cpp"):
            os.remove("wmain.cpp")

        print("Copying file...")
        shutil.copy(path, "wmain.cpp")

        print("Changing handlers... \t(1/5)")
        chunk = open("chunck.txt")
        chunck1 = open("chunck1.txt")
        Utils.replace_chunck("main.cpp", "wmain.cpp", chunk.read(), chunck1.read())

        print("Changing description... (2/5)")
        Utils.remove("wmain.cpp", " * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system\n")
        Utils.add(3, "wmain.cpp", " * PROJECT: Termi-Windows version with OpenGL and Dear ImGui rendering system\n")

        print("Changing handlers... \t(3/5)")
        Utils.remove("wmain.cpp", "#include <signal.h>\n")
        Utils.add(17, "wmain.cpp", "#include <Windows.h>\n")

        print("Changing handlers... \t(4/5)")
        Utils.remove("wmain.cpp", "struct sigaction sigIntHandler;\n")

        print("Changing description... (5/5)")
        Utils.remove("wmain.cpp", " * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL\n")
        Utils.add(5, "wmain.cpp", " * INFORAMTION: Compile solution, else check Victor Gordan's video\n")

        print("Removing (GNU/)Linux file...")
        os.remove("main.cpp")
        os.rename("wmain.cpp", "main.cpp")

        return 0
    except Exception as error:
        print("Exception occured!")
        print(error)
        print("Returning 1...")

def generate_cpp(path : str) -> int:
    print("Copying file...")
    shutil.copy(path, "wimgui_code.cpp")
    return 0

def generate_hpp(path : str) -> int:
    print("Copying file...")
    shutil.copy(path, "wimgui_code.hpp")
    return 0

def generate(path : str, which : int) -> int:
    status = None

    if which == 1:
        status = generate_main(path)
    
    elif which == 2:
        status = generate_cpp(path)

    elif which == 3:
        status = generate_hpp(path)

    else:
        print(f"Unknown 'which' parameter: '{which}'!")
        return 2

    return status

def main(path: str, which : int) -> int:
    try:
        file = open(path)
    except FileNotFoundError as file_error:
        print(file_error)
        print("Exiting...")
        return 1

    print("Basic (GNU/)Linux informations: ")
    print(f"\t name: {file.name}")
    print(f"\t encoding: {file.encoding}")
    print(f"\t open mode: {file.mode}")

    print(" ")

    return generate(file.name, which)
    
if __name__ == "__main__":
    print("Windows version generator.\nIt generates code for Windows 7 as minium Windows version.")
    print("Also create backup of (GNU/)Linux file.\n")

    if not len(sys.argv) == 3:
        file = input("Enter path of (GNU/)Linux file: ")
        which = int(input("Which file to generate? [1 - main, 2 - Dear ImGui C++ file, 3 - Dear ImGui header]: "))
        main(str(file), int(which))

    main(str(sys.argv[1]), int(sys.argv[2]))