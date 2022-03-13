clear

g++ -o bin/OpenCalc Commands/OpenCalc.cpp
g++ -o bin/filesys Commands/Filesys.cpp
g++ -o bin/GeoCalc Commands/GeoCalc.cpp

clear

rm -rf ./Termi
g++ -o Termi main.cpp
./Termi
