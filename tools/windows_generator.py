'''
AUTHOR:      Andrej Bartulin
PROJECT:     Termi's Windows version generator
LICENSE:     ringwormGO General License 1.0 | (RGL) 2022
DESCRIPTION: Main file for generator
'''

from os import stat
import sys
import shutil

def generate_main(path : str) -> int:
    print("Copying file...")
    shutil.copy(path, "wmain.cpp")
    return 0

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