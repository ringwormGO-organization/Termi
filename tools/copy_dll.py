'''
AUTHOR:      Andrej Bartulin
PROJECT:     Copies .dll file from Termi-GUI project to Termi-Main project
LICENSE:     ringwormGO General License 1.0 | (RGL) 2022
DESCRIPTION: Main file
REQUIRED PACKAGES: shutil
'''

import os
import shutil

cwd: str = os.getcwd()

if cwd.endswith("tools"):
    os.chdir("../Termi-Windows/Termi-GUI/x64/Debug")
    print(os.getcwd())

else:
    print("Please enter `tools` directory")

shutil.copy("Termi-GUI.dll", "../../../Termi-Main/bin/Debug/net6.0/Termi-GUI.dll")
print("Done")
