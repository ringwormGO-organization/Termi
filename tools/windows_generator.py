# Archived currently

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

    def write_new_command(self, windows_cpp_path: str, windows_hpp_path: str, print_no_new_commands: bool):
        current_commands = [] # commands from file
        old_commands = [] # commands from github

        # We are gonna check (GNU/Linux's) imgui_code.hpp and Windows's imgui_code.hpp from GitHub
        url = "https://raw.githubusercontent.com/ringwormGO-organization/Termi/main/Termi-Windows/Termi-OpenGL/imgui_code.hpp"
        response = requests.get(url)
        open(f"wimgui_code.hpp", "wb").write(response.content)

        # get current commands
        with open(windows_hpp_path, "r", encoding="utf8") as f:
            for i in f:
                if i.startswith("    {\"") and i.endswith("},\n") or i.startswith("    {\"yes"): # spaces because we use spaces in file
                    i = i[6:i.find(',')]
                    i = i[:-1]
                    current_commands.append(i)

        # get windows commands
        with open("wimgui_code.hpp", "r", encoding="utf8") as g:
            for j in g:
                if j.startswith("    {\"") and j.endswith("},\n") or j.startswith("    {\"yes"): # spaces because we use spaces in file
                    j = j[6:j.find(',')]
                    j = j[:-1]
                    old_commands.append(j)

        # get new command/commands
        new_commands = self.__get_new_command(self, current_commands, old_commands)

        if len(new_commands) == 0:
            if print_no_new_commands:
                print("There is no new commands!")
        
        else:
            print(colorama.Fore.BLUE + "TODO: Sort by alphabetical order!")
            print("TODO: Automatically remove (GNU/)Linux command code!" + colorama.Fore.RESET)

            new_command = input("Enter file which contains Windows command: ")
            new_command_text = open(new_command).read()

            windows_file = open(windows_cpp_path, "a+")
            windows_file.write("\n" + new_command_text + "\n" + "/* windows code */\n")

            print(colorama.Fore.LIGHTRED_EX + "Please remove (GNU/)Linux command code!" + colorama.Fore.RESET)

            os.remove("wimgui_code.hpp")

        return 0

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
        Utils.replace_chunck(Utils, "main.cpp", "wmain.cpp", chunck0.read(), chunck1.read())

        print(colorama.Fore.YELLOW + "Changing description... (2/5)" + colorama.Fore.RESET)
        Utils.remove(Utils, 'w' + path, " * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system\n")
        Utils.add(Utils, 3, 'w' + path, " * PROJECT: Termi-Windows version with OpenGL and Dear ImGui rendering system\n")

        print(colorama.Fore.YELLOW + "Changing handlers... \t(3/5)" + colorama.Fore.RESET)
        Utils.remove(Utils, 'w' + path, "#include <signal.h>\n")
        Utils.add(Utils, 17, 'w' + path, "#include <Windows.h>\n")

        print(colorama.Fore.YELLOW + "Changing handlers... \t(4/5)" + colorama.Fore.RESET)
        Utils.remove(Utils, 'w' + path, "struct sigaction sigIntHandler;\n")

        print(colorama.Fore.YELLOW + "Changing description... (5/5)" + colorama.Fore.RESET)
        Utils.remove(Utils, 'w' + path, " * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && make && ./Termi-OpenGL\n")
        Utils.add(Utils, 5, 'w' + path, " * INFORAMTION: Compile solution, else check Victor Gordan's video\n")

        print(colorama.Fore.YELLOW + "Removing (GNU/)Linux file..." + colorama.Fore.RESET)
        os.remove("main.cpp")
        os.rename("wmain.cpp", "main.cpp")

        return 0
    except Exception as error:
        print(colorama.Fore.LIGHTRED_EX + "Exception occured!" + colorama.Fore.RESET)
        print(error)
        print("Returning 1...")

def generate_cpp(path : str) -> int:
    try:
        print(colorama.Fore.YELLOW + "Copying file..." + colorama.Fore.RESET)
        shutil.copy(path, "wimgui_commands.cpp")

        print(colorama.Fore.YELLOW + "Changing commands... (1/1)" + colorama.Fore.RESET)
        chunck2 = open("chunck2.txt")
        chunck3 = open("chunck3.txt")
        Utils.replace_chunck(Utils, "imgui_commands.cpp", "wimgui_commands.cpp", chunck2.read(), chunck3.read())

        print(colorama.Fore.YELLOW + "Changing description... (2/2)" + colorama.Fore.RESET)
        Utils.remove(Utils, 'w' + path, " * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system\n")
        Utils.add(Utils, 3, 'w' + path, " * PROJECT: Termi-Windows version with OpenGL and Dear ImGui rendering system\n")

        print(colorama.Fore.YELLOW + "Changing description... (3/3)" + colorama.Fore.RESET)
        Utils.remove(Utils, 'w' + path, " * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && make && ./Termi-OpenGL\n")
        Utils.add(Utils, 5, 'w' + path, " * INFORAMTION: Compile solution, else check Victor Gordan's video\n")

        print(colorama.Fore.YELLOW + "Removing (GNU/)Linux file..." + colorama.Fore.RESET)
        os.remove("imgui_commands.cpp")
        os.rename("wimgui_commands.cpp", "imgui_commands.cpp")

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
        Utils.replace_chunck(Utils, "imgui_code.hpp", "wimgui_code.hpp", chunck4.read(), chunck5.read())

        print(colorama.Fore.YELLOW + "Changing description... (2/3)" + colorama.Fore.RESET)
        Utils.remove(Utils, 'w' + path, " * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system\n")
        Utils.add(Utils, 3, 'w' + path, " * PROJECT: Termi-Windows version with OpenGL and Dear ImGui rendering system\n")

        print(colorama.Fore.YELLOW + "Changing description... (3/3)" + colorama.Fore.RESET)
        Utils.remove(Utils, 'w' + path, " * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && make && ./Termi-OpenGL\n")
        Utils.add(Utils, 5, 'w' + path, " * INFORAMTION: Compile solution, else check Victor Gordan's video\n")

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

def main(files_path) -> int:
    status = None

    for i in files_path:
        try:
            file = open(i)

            print("Basic (GNU/)Linux file information: ")
            print(f"\t name: {file.name}")
            print(f"\t encoding: {file.encoding}")
            print(" ")

            file.close()

            if i.endswith("main.cpp"):
                status = generate_main(i)

                if status != 0:
                    exit(status)

            elif i.endswith("imgui_commands.cpp"):
                status = generate_cpp(i)

                if status != 0:
                    exit(status)
        
            elif i.endswith("imgui_code.hpp"):
                status = generate_hpp(i)

                if status != 0:
                    exit(status)

            print(" ")

        except FileNotFoundError as file_error:
            print(colorama.Fore.LIGHTRED_EX + f"File {i} not found!\nExiting..." + colorama.Fore.RESET)
            exit(1)

    print(colorama.Fore.YELLOW + "Searching for new commands..." + colorama.Fore.RESET)
    status = Utils.write_new_command(Utils, "imgui_commands.cpp", "imgui_code.hpp", False)

    if status != 0:
        exit(status)

    print(" ")
    
if __name__ == "__main__":
    utils = Utils()
    colorama.init()

    print(colorama.Fore.LIGHTRED_EX + "Termi's Windows code generator.".center(100))
    print("It generates code for Windows 7 as minium Windows version.".center(100) + colorama.Fore.RESET)
    print(colorama.Fore.LIGHTYELLOW_EX + "Internet connection required!".center(100) + colorama.Fore.RESET)
    print(colorama.Fore.LIGHTGREEN_EX + "Archived currently!".center(100) + colorama.Fore.RESET)
    print(" ")

    if len(sys.argv) >= 1 and len(sys.argv) != 2 and len(sys.argv) != 4:
        print(colorama.Fore.LIGHTYELLOW_EX + f"Wrong number ({len(sys.argv) - 1}) of arguments! See list down below..." + colorama.Fore.RESET) # light yellow because of estetics
        print("Arguments:")

        sys.stdout.write(colorama.Fore.CYAN + "\t default/automatic mode = " + colorama.Fore.RESET)
        print("path of (GNU/)Linux files, relevant to: ")
        print("main.cpp, imgui_commands.cpp and imgui_code.hpp".center(100))

        sys.stdout.write(colorama.Fore.CYAN + "\t download code chuncks = " + colorama.Fore.RESET)
        print("-d")

        sys.stdout.write(colorama.Fore.CYAN + "\t few notes = " + colorama.Fore.RESET)
        print("-n")

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

    elif sys.argv[1] == '-n':
        seperator = "-" * 90

        print(colorama.Fore.LIGHTYELLOW_EX + "Notes: " + colorama.Fore.RESET) # light yellow because of estetics
        print("Files which are refered to '(GNU/)Linux' files are files made for POSIX standard.")
        print("You can compile those files for platforms which support POSIX and OpenGL ((GNU/)Linux, BSD, macOS), ")
        print("but other platforms which are not (GNU/)Linux are not fully supported")
        print(seperator.center(100))
        print("We are calling those files '(GNU/)Linux' files because of this two reasons: ")
        print("\t 1. Fully supported by ringwormGO for (GNU/)Linux")
        print("and".center(100))
        print("\t 2. As Richard Stallman said, " + colorama.Fore.LIGHTCYAN_EX + "Linux is another free component of a fully functioning (GNU) system..." + colorama.Fore.RESET)
        print("\t To have functional system we need add libraries on top of kernel like GNU and")
        print("\t distros like Debian, Ubuntu, Fedora, Arch, etc. are " + colorama.Fore.YELLOW + "GNU/Linux " + colorama.Fore.RESET + "distros because they use GNU, ")
        print("\t but distros like Alpine don't use GNU so they can't be GNU/Linux so we call them")
        print("\t just a 'Linux' distro, but they might have their name we just don't know at moment.")
        print(seperator.center(100))
        print("If you found issue or want new feature " + colorama.Fore.LIGHTMAGENTA_EX + "please first check our GitHub for similar issues" + colorama.Fore.RESET + "so we can reduce duplicates, ")
        print("but if you don't found similar issue, fell free to create new one.")
        print("For creating pull requets check CONTRIBUTING.md file located in root of repo!")
        print(seperator.center(100))
        print("Thank you for choosing Termi")
        print(u"2021-present ringwormGO")
        print("btw, code is licensed by ringwormGO General License 1.0 | (RGL) 2022")
        print(" ")

    elif sys.argv[1] == '-c':
        print(colorama.Fore.LIGHTYELLOW_EX + "This is only for generator developers!" + colorama.Fore.RESET)

        if exists("main.cpp"):
            os.remove("main.cpp")

        if exists("imgui_commands.cpp"):
            os.remove("imgui_commands.cpp")

        if exists("imgui_code.hpp"):
            os.remove("imgui_code.hpp")

        try:
            shutil.copy("../Termi-Linux-OpenGL/main.cpp", "main.cpp")
            shutil.copy("../Termi-Linux-OpenGL/imgui_commands.cpp", "imgui_commands.cpp")
            shutil.copy("../Termi-Linux-OpenGL/imgui_code.hpp", "imgui_code.hpp")

        except FileNotFoundError as file_error:
            print(colorama.Fore.LIGHTRED_EX + "Exception occured!")
            print(file_error.strerror + colorama.Fore.RESET)

        print(colorama.Fore.LIGHTGREEN_EX + "Done!" + colorama.Fore.RESET)
    
    else:
        files = []
        files.append(sys.argv[1])
        files.append(sys.argv[2])
        files.append(sys.argv[3])

        try:
            main(files)
        except KeyboardInterrupt as interrupt:
            print(colorama.Fore.LIGHTRED_EX + "\nKeyboard interrupt!\nExiting..." + colorama.Fore.RESET)
            print(interrupt)
            exit(0)

        print(colorama.Fore.LIGHTGREEN_EX + "Done!" + colorama.Fore.RESET)
