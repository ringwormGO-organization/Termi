clear

rm -rf ./bin/OpenCalc
rm -rf ./bin/filesys
rm -rf ./bin/GeoCalc
rm -rf ./bin/neofetch

g++ -o bin/OpenCalc Commands/OpenCalc.cpp
g++ -o bin/filesys Commands/Filesys.cpp
g++ -o bin/GeoCalc Commands/GeoCalc.cpp
g++ -o bin/neofetch Commands/Neofetch.cpp

clear

rm -rf ./Termi
g++ -o Termi main.cpp
./Termi
