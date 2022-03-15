cls

cl /EHsc Commands/OpenCalc.cpp
move OpenCalc.exe bin/OpenCalc.exe
del OpenCalc.obj

cl /std:c++20 /EHsc Commands/filesys.cpp
move filesys.exe bin/filesys.exe
del filesys.obj

cl /EHsc Commands/GeoCalc.cpp
move GeoCalc.exe bin/GeoCalc.exe
del GeoCalc.obj

cl /EHsc Commands/help.cpp
move help.exe bin/help.exe
del help.obj

cl /EHsc Commands/Neofetch.cpp
move Neofetch.exe bin/Neofetch.exe
del Neofetch.obj