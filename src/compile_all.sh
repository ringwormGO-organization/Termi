clear

cd Termi-Commands
cmake --build . --target clean
cmake . && make
cp libTermi-Commands.so ../Termi-Main
echo " "

cd ../Termi-GUI
cmake --build . --target clean
cmake . && make
cp libTermi-GUI.so ../Termi-Main
echo " "

cd ../Termi-Main
cmake --build . --target clean
cmake . && make

echo " "
LD_LIBRARY_PATH=. ./Termi-Main
cd ../
