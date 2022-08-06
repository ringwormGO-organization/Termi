'''
AUTHOR:      Andrej Bartulin
PROJECT:     Termi's Windows version generator
LICENSE:     ringwormGO General License 1.0 | (RGL) 2022
DESCRIPTION: Main file for generator
REQUIRED PACKAGES: os, os.path, requests, sys, shutil, string
'''

import os
from os.path import exists
import requests
import sys
import shutil

class Utils:
    def __init__(self):
        self.__commands = ["base64", "calc", "cd", "change-setting", "echo", "geocalc", "list", "mkdir",
                    "neofetch", "openfile", "time", "rm", "whoami", "writefile", "yes"]

    def __command_id(self, line: str) -> int:
        for i in self.__commands:
            if line == f"int {i}(std::vector<std::string>& vect)\n":
                return i

    def remove(self, path : str, text : str):
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

    def write_new_command(self, linux_file_path: str, windows_file_path: str):
        linux_commands = []
        windows_commands = []
        lines_to_remove = []

        with open(linux_file_path) as file_in:
            for i in file_in:
                # sys.stdout.write(i)
                if (i == f"int {self.__command_id(i)}(std::vector<std::string>& vect)\n"):
                    linux_commands.append(i)
                else:
                    lines_to_remove.append(i)

        for i in lines_to_remove:
            self.remove(linux_file_path, i)

        lines_to_remove.clear()

        with open(windows_file_path) as file_in:
            for i in file_in:
                # sys.stdout.write(i)
                if (i == f"int {self.__command_id(i)}(std::vector<std::string>& vect)\n"):
                    windows_commands.append(i)
                else:
                    lines_to_remove.append(i)

        for i in lines_to_remove:
            self.remove(windows_file_path, i)

        if len(linux_commands) == len(windows_commands) and len(linux_commands) == sum([1 for i, j in zip(linux_commands, windows_commands) if i == j]):
            print ("The lists are identical")
        else:
            print ("The lists are not identical")

    def return_link(chunck_id : int) -> str:
        return "https://raw.githubusercontent.com/ringwormGO-organization/Termi/main/tools/chunck" + str(chunck_id) + ".txt"

    def commands(self, new_command=None):
        if new_command != None:
            self.__commands.append(new_command)

        return sorted(self.__commands)

def generate_main(path : str) -> int:
    try:
        if exists("wmain.cpp"):
            os.remove("wmain.cpp")

        print("Copying file...")
        shutil.copy(path, "wmain.cpp")

        print("Changing handlers... \t(1/5)")
        chunck0 = open("chunck0.txt")
        chunck1 = open("chunck1.txt")
        Utils.replace_chunck("main.cpp", "wmain.cpp", chunck0.read(), chunck1.read())

        print("Changing description... (2/5)")
        Utils.remove('w' + path, " * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system\n")
        Utils.add(3, 'w' + path, " * PROJECT: Termi-Windows version with OpenGL and Dear ImGui rendering system\n")

        print("Changing handlers... \t(3/5)")
        Utils.remove('w' + path, "#include <signal.h>\n")
        Utils.add(17, 'w' + path, "#include <Windows.h>\n")

        print("Changing handlers... \t(4/5)")
        Utils.remove('w' + path, "struct sigaction sigIntHandler;\n")

        print("Changing description... (5/5)")
        Utils.remove('w' + path, " * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL\n")
        Utils.add(5, 'w' + path, " * INFORAMTION: Compile solution, else check Victor Gordan's video\n")

        print("Removing (GNU/)Linux file...")
        os.remove("main.cpp")
        os.rename("wmain.cpp", "main.cpp")

        chunck0.close()
        chunck1.close()

        return 0
    except Exception as error:
        print("Exception occured!")
        print(error)
        print("Returning 1...")

def generate_cpp(path : str) -> int:
    try:
        print("Copying file...")
        shutil.copy(path, "wimgui_code.cpp")

        print("Changing commands... (1/3)")
        chunck2 = open("chunck2.txt")
        chunck3 = open("chunck3.txt")
        Utils.replace_chunck("imgui_code.cpp", "wimgui_code.cpp", chunck2.read(), chunck3.read())

        print("Changing description... (2/3)")
        Utils.remove('w' + path, " * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system\n")
        Utils.add(3, 'w' + path, " * PROJECT: Termi-Windows version with OpenGL and Dear ImGui rendering system\n")

        print("Changing description... (3/3)")
        Utils.remove('w' + path, " * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL\n")
        Utils.add(5, 'w' + path, " * INFORAMTION: Compile solution, else check Victor Gordan's video\n")

        print("Removing (GNU/)Linux file...")
        os.remove("imgui_code.cpp")
        os.rename("wimgui_code.cpp", "imgui_code.cpp")

        chunck2.close()
        chunck3.close()

        return 0
    except Exception as error:
        print("Exception occured!")
        print(error)
        print("Returning 1...")

def generate_hpp(path : str) -> int:
    try:
        print("Copying file...")
        shutil.copy(path, "wimgui_code.hpp")

        print("Changing commands... (1/3)")
        chunck4 = open("chunck4.txt")
        chunck5 = open("chunck5.txt")
        Utils.replace_chunck("imgui_code.hpp", "wimgui_code.hpp", chunck4.read(), chunck5.read())

        print("Changing description... (2/3)")
        Utils.remove('w' + path, " * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system\n")
        Utils.add(3, 'w' + path, " * PROJECT: Termi-Windows version with OpenGL and Dear ImGui rendering system\n")

        print("Changing description... (3/3)")
        Utils.remove('w' + path, " * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL\n")
        Utils.add(5, 'w' + path, " * INFORAMTION: Compile solution, else check Victor Gordan's video\n")

        print("Removing (GNU/)Linux file...")
        os.remove("imgui_code.hpp")
        os.rename("wimgui_code.hpp", "imgui_code.hpp")

        chunck4.close()
        chunck5.close()

        return 0
    except Exception as error:
        print("Exception occured!")
        print(error)
        print("Returning 1...")

def generate(path : str, which : int) -> int:
    status = None

    which = int(which)

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
    utils = Utils()

    print("Windows version generator.\nIt generates code for Windows 7 as minium Windows version.")
    print("Also create backup of (GNU/)Linux file.")
    print("Arguments:")
    print("\t argv[1] - path of (GNU/Linux) file")
    print("\t which file to generate [1 - main, 2 - Dear ImGui C++ file, 3 - Dear ImGui header]")
    print("\t to download chuncks of code, type in first argument `-d`")
    print("\t to add new command, type in first argument `-a`\n")

    if len(sys.argv) == 1:
        exit(0)

    elif sys.argv[1] == '-d':
        for i in range(6):
            if exists(f"chunck{i}.txt"):
                os.remove(f"chunck{i}.txt")

        for i in range(6):
            url = utils.return_link(i)
            response = requests.get(url)
            open(f"chunck{i}.txt", "wb").write(response.content)

    elif sys.argv[1] == '-a':
        print("WIP, not finished yet!")
        print("TODO: Sort by alphabetical order!")

        if (len(sys.argv) != 4):
            print("There is no enough arguments!")
            exit(0)

        # writing new command to file
        utils.write_new_command(sys.argv[2], sys.argv[3])
    
    else:
        main(sys.argv[1], sys.argv[2])
