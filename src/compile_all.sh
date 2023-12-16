#!/bin/sh
clear
if [ -z $1 ]; then
    threads=2
else
    threads=$1
fi
echo "Number of threads: $threads"
cd Termi-Commands
cmake --build . --target clean
cmake . && make -j $threads
cp libTermi-Commands.so ../Termi-Main
echo " "

cd ../Termi-GUI
cmake --build . --target clean
cmake . && make -j $threads
cp libTermi-GUI.so ../Termi-Main
echo " "

cd ../Termi-Main
cmake --build . --target clean
cmake . && make -j $threads

echo " "
LD_LIBRARY_PATH=. ./Termi-Main
cd ../
