clear

cd Termi-Commands
cmake . && make
cp libTermi-Commands.so ../Termi-Main
echo " "

cd ../Termi-GUI
cmake . && make
cp libTermi-GUI.so ../Termi-Main
echo " "

cd ../Termi-Main
cmake . && make

echo " "
LD_LIBRARY_PATH=. ./Termi-Main
cd ../
