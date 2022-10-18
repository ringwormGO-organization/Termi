clear

cd Termi-Commands
cmake . && make
cp libTermi-Commands.so ../Termi-Main

cd ../Termi-GUI
cmake . && make
cp libTermi-GUI.so ../Termi-Main

cd ../Termi-Main
cmake . && make

LD_LIBRARY_PATH=. ./Termi-Main
cd ../
