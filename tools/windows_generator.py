'''
AUTHOR:      Andrej Bartulin
PROJECT:     Termi's Windows version generator
LICENSE:     ringwormGO General License 1.0 | (RGL) 2022
DESCRIPTION: Main file for generator
'''

import sys

def main(path : str) -> int:
    print(f"Path is: ", path)

if __name__ == "__main__":
    if not len(sys.argv) == 1:
        path = input("Enter path of file of (GNU/)Linux file: ")
        main(path)

    main(sys.argv[1])