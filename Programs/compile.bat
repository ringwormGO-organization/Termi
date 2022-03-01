cls

cl /EHsc Linux/Calculator.cpp
move Calculator.exe bin/Calculator.exe
del Calculator.obj

cl /EHsc Linux/GeoCalculator.cpp
move GeoCalculator.exe bin/GeoCalculator.exe
del GeoCalculator.obj

cl /EHsc Linux/help.cpp
move help.exe bin/help.exe
del help.obj