'''
AUTHOR:      Andrej Bartulin
PROJECT:     Termi's Windows version generator
LICENSE:     ringwormGO General License 1.0 | (RGL) 2022
DESCRIPTION: Main file for generator
REQUIRED PACKAGES: os, os.path, requests, sys, shutil, string, colorama
'''

import os
from os.path import exists
import requests
import sys
import shutil

import colorama

'''
    Naming convention for colors:
        CYAN - arguments description
        WHITE (it is more gray than white) - variables
        ORANGE (it is more orange than yellow) - state of execution

        LIGHTRED_EX - error and title
        LIGHTYELLOW_EX - warning
        LIGHTGREEN_EX - success
        LIGHTBLUE_EX - notes about instability of program
'''

class Utils:
    def __init__(self):
        # commands name, points to function name in files
        # currently there is no point to have this, but it looks cool, i hope, idk anymore is it cool
        self.__commands = ["base64", "calc", "cd", "change_setting", "echo", "find_command", "geocalc", "list_dir", "new_dir",
                    "neofetch", "openfile", "ttime", "rm", "whoami", "writefile", "yes"]

    def __command_id(self, line: str) -> int:
        for i in self.__commands:
            if line == f"int {i}(std::vector<std::string>& vect)\n":
                return i

    def __get_new_command(self, linux_commands, windows_commands):
        linux_only = []
        for i in linux_commands:
            if i not in windows_commands:
                linux_only.append(i)

        return linux_only

    def remove(self, path : str, text : str):
        with open(path, "r+") as f:
            d = f.readlines()
            f.seek(0)
            for i in d:
                if i != text:
                    f.write(i)
            f.truncate()

    def replace_chunck(self, read_path : str, write_path : str, starter_text: str, new_text: str):
        if starter_text == "":
            starter_text = open(read_path, "r").read()
         
        # Read in the file
        with open(read_path, 'r') as file :
            filedata = file.read()

        # Replace the target string
        filedata = filedata.replace(starter_text, new_text)

        # Write the file out again
        with open(write_path, 'w') as file:
            file.write(filedata)

    def add(self, index : int, path : str, text : str):
        with open(path, "r") as f:
            contents = f.readlines()

        contents.insert(index, text)

        with open(path, "w") as f:
            contents = "".join(contents)
            f.write(contents)

    def write_new_command(self, linux_file_path: str, windows_file_path: str):
        linux_commands = [] # linux commands
        windows_commands = [] # windows commands

        line_to_write_new_command: int = 0 # line to write new command

        content_before_new_command: str = "" # file contnet before line meant to write new command
        content_after_new_command: str = "" # file contnet after line meant to write new command

        # get linux commands
        with open(linux_file_path, "r") as f:
            for i in f:
                if i.endswith("std::vector<std::string>& vect)\n"):
                    linux_commands.append(i)

        # get windows commands, line to write new command, content before new command and content after new command
        file = open(windows_file_path, "r")
        append_before: bool = True
        append_after: bool = False
        for line_no, line in enumerate(file):
            if line == f"int {self.__command_id(line)}(std::vector<std::string>& vect)\n":
                windows_commands.append(line)

            if line.startswith("Console::Console"):
                line_to_write_new_command = line_no
                append_before = False
                append_after = True

            if append_before:
                content_before_new_command += line

            if append_after:
                content_after_new_command += line
        file.close()

        # get new command/commands
        new_commands = self.__get_new_command(linux_commands, windows_commands)

        if len(new_commands) == 0:
            print("There is no new commands!")
        
        else:
            print("New commands are: ")
            for i in new_commands:
                sys.stdout.write(colorama.Fore.WHITE + i[4:i.find("(")] + ", ")
            sys.stdout.write(colorama.Fore.RESET + "\n")
            print("Full array: ")
            print(colorama.Fore.WHITE + str(new_commands) + colorama.Fore.RESET)

            # get code for new command
            new_command_path = input("Enter path to file with contains code for new Windows command: ")
            new_command_text = open(new_command_path, "r").read()
            new_command_text += "\n\n"

            # set line to write new command (again)
            line_to_write_new_command = line_to_write_new_command - 5

            # write content before new command and content after in "temp_chunck.txt" file
            with open("temp_chunck.txt", "w") as f:
                f.write(content_before_new_command)
                f.write(content_after_new_command)

            # add new command using replace function, we are replacing content before with new command and content after the new command
            # and then we are removing "temp_chunck.txt" file
            self.replace_chunck("temp_chunck.txt", windows_file_path, "", (content_before_new_command + new_command_text + content_after_new_command))
            os.remove("temp_chunck.txt")

    def return_link(self, chunck_id : int) -> str:
        return "https://raw.githubusercontent.com/ringwormGO-organization/Termi/main/tools/chunck" + str(chunck_id) + ".txt"

def generate_main(path : str) -> int:
    try:
        if exists("wmain.cpp"):
            os.remove("wmain.cpp")

        print(colorama.Fore.YELLOW + "Copying file..." + colorama.Fore.RESET)
        shutil.copy(path, "wmain.cpp")

        print(colorama.Fore.YELLOW + "Changing handlers... \t(1/5)" + colorama.Fore.RESET)
        chunck0 = open("chunck0.txt")
        chunck1 = open("chunck1.txt")
        Utils.replace_chunck("main.cpp", "wmain.cpp", chunck0.read(), chunck1.read())

        print(colorama.Fore.YELLOW + "Changing description... (2/5)" + colorama.Fore.RESET)
        Utils.remove('w' + path, " * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system\n")
        Utils.add(3, 'w' + path, " * PROJECT: Termi-Windows version with OpenGL and Dear ImGui rendering system\n")

        print(colorama.Fore.YELLOW + "Changing handlers... \t(3/5)" + colorama.Fore.RESET)
        Utils.remove('w' + path, "#include <signal.h>\n")
        Utils.add(17, 'w' + path, "#include <Windows.h>\n")

        print(colorama.Fore.YELLOW + "Changing handlers... \t(4/5)" + colorama.Fore.RESET)
        Utils.remove('w' + path, "struct sigaction sigIntHandler;\n")

        print(colorama.Fore.YELLOW + "Changing description... (5/5)" + colorama.Fore.RESET)
        Utils.remove('w' + path, " * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL\n")
        Utils.add(5, 'w' + path, " * INFORAMTION: Compile solution, else check Victor Gordan's video\n")

        print(colorama.Fore.YELLOW + "Removing (GNU/)Linux file..." + colorama.fore.RESET)
        os.remove("main.cpp")
        os.rename("wmain.cpp", "main.cpp")

        chunck0.close()
        chunck1.close()

        return 0
    except Exception as error:
        print(colorama.Fore.LIGHTRED_EX + "Exception occured!" + colorama.Fore.RESET)
        print(error)
        print("Returning 1...")

def generate_cpp(path : str) -> int:
    try:
        print(colorama.Fore.YELLOW + "Copying file..." + colorama.Fore.RESET)
        shutil.copy(path, "wimgui_code.cpp")

        print(colorama.Fore.YELLOW + "Changing commands... (1/3)" + colorama.Fore.RESET)
        chunck2 = open("chunck2.txt")
        chunck3 = open("chunck3.txt")
        Utils.replace_chunck("imgui_code.cpp", "wimgui_code.cpp", chunck2.read(), chunck3.read())

        print(colorama.Fore.YELLOW + "Changing description... (2/3)" + colorama.Fore.RESET)
        Utils.remove('w' + path, " * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system\n")
        Utils.add(3, 'w' + path, " * PROJECT: Termi-Windows version with OpenGL and Dear ImGui rendering system\n")

        print(colorama.Fore.YELLOW + "Changing description... (3/3)" + colorama.Fore.RESET)
        Utils.remove('w' + path, " * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL\n")
        Utils.add(5, 'w' + path, " * INFORAMTION: Compile solution, else check Victor Gordan's video\n")

        print(colorama.Fore.YELLOW + "Removing (GNU/)Linux file..." + colorama.Fore.RESET)
        os.remove("imgui_code.cpp")
        os.rename("wimgui_code.cpp", "imgui_code.cpp")

        chunck2.close()
        chunck3.close()

        return 0
    except Exception as error:
        print(colorama.Fore.LIGHTRED_EX + "Exception occured!" + colorama.Fore.RESET)
        print(error)
        print("Returning 1...")

def generate_hpp(path : str) -> int:
    try:
        print(colorama.Fore.YELLOW + "Copying file..." + colorama.Fore.RESET)
        shutil.copy(path, "wimgui_code.hpp")

        print(colorama.Fore.YELLOW + "Changing commands... (1/3)" + colorama.Fore.RESET)
        chunck4 = open("chunck4.txt")
        chunck5 = open("chunck5.txt")
        Utils.replace_chunck("imgui_code.hpp", "wimgui_code.hpp", chunck4.read(), chunck5.read())

        print(colorama.Fore.YELLOW + "Changing description... (2/3)" + colorama.Fore.RESET)
        Utils.remove('w' + path, " * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system\n")
        Utils.add(3, 'w' + path, " * PROJECT: Termi-Windows version with OpenGL and Dear ImGui rendering system\n")

        print(colorama.Fore.YELLOW + "Changing description... (3/3)" + colorama.Fore.RESET)
        Utils.remove('w' + path, " * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL\n")
        Utils.add(5, 'w' + path, " * INFORAMTION: Compile solution, else check Victor Gordan's video\n")

        print(colorama.Fore.YELLOW + "Removing (GNU/)Linux file..." + colorama.Fore.RESET)
        os.remove("imgui_code.hpp")
        os.rename("wimgui_code.hpp", "imgui_code.hpp")

        chunck4.close()
        chunck5.close()

        return 0
    except Exception as error:
        print(colorama.Fore.LIGHTRED_EX + "Exception occured!" + colorama.Fore.RESET)
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
        print(colorama.Fore.LIGHTRED_EX + "File not found!\nExiting..." + colorama.Fore.RESET)
        return 1

    print("Basic (GNU/)Linux informations: ")
    print(f"\t name: {file.name}")
    print(f"\t encoding: {file.encoding}")
    print(f"\t open mode: {file.mode}")

    print(" ")

    return generate(file.name, which)
    
if __name__ == "__main__":
    utils = Utils()
    colorama.init()

    print(colorama.Fore.LIGHTRED_EX + "Termi's Windows code generator.".center(100))
    print("It generates code for Windows 7 as minium Windows version.".center(100) + colorama.Fore.RESET)
    print("Also creates backup of (GNU/)Linux file.")
    print("Arguments:")
    print(colorama.Fore.CYAN + "\t argv[1] - path of (GNU/Linux) file")
    print("\t which file to generate [1 - main, 2 - Dear ImGui C++ file, 3 - Dear ImGui header]")
    print("\t to download chuncks of code, type in first argument `-d`")
    print("\t to add new command in windows file, type in first argument `-a`")
    print("\t to add new command, type in first argument `-a`\n" + colorama.Fore.RESET)

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

        print(colorama.Fore.LIGHTGREEN_EX + "Done!" + colorama.Fore.RESET)

    elif sys.argv[1] == '-a':
        print(colorama.Fore.LIGHTBLUE_EX + "WIP, not finished yet!")
        print("TODO: Sort by alphabetical order!" + colorama.Fore.RESET)

        if (len(sys.argv) != 4):
            print(colorama.Fore.LIGHTRED_EX + "There is no enough arguments!" + colorama.Fore.RESET)
            exit(0)

        # writing new command to file
        try:
            utils.write_new_command(sys.argv[2], sys.argv[3])
            print(colorama.Fore.LIGHTGREEN_EX + "Done!" + colorama.Fore.RESET)
        except KeyboardInterrupt as error:
            print(colorama.Fore.LIGHTRED_EX + "\nKeyboard interrupt!\nExiting..." + colorama.Fore.RESET)
            print(error)
            exit(0)
    
    else:
        main(sys.argv[1], sys.argv[2])
        print(colorama.Fore.LIGHTGREEN_EX + "Done!" + colorama.Fore.RESET)