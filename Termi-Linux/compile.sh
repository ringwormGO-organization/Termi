clear

rm -rf ./bin/OpenCalc
rm -rf ./bin/filesys
rm -rf ./bin/GeoCalc
rm -rf ./bin/neofetch

g++ -g -o bin/OpenCalc Commands/OpenCalc.cpp
g++ -g -o bin/filesys Commands/Filesys.cpp
g++ -g -o bin/GeoCalc Commands/GeoCalc.cpp
g++ -g -o bin/neofetch Commands/Neofetch.cpp

clear

rm -rf ./Termi
g++ -g -o Termi main.cpp
./Termi
