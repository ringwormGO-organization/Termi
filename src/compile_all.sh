#!/bin/sh
clear
if [ -z $1 ]; then
    threads=2
else
    threads=$1
fi

echo "Number of threads: $threads"

build() {
    cd "$1"

    mkdir -p build/
    cd build

    if [ -n "$2" ] && [ "$2" = "clean" ]; then
        cmake --build . --target clean
    fi

    cmake .. && make -j $threads

    if [ -n "$3" ] && [ "$3" = "library" ]; then
        cp "lib$1.so" ../../Termi-Main/build
    elif [ -n "$2" ] && [ "$2" = "library" ]; then
        cp "lib$1.so" ../../Termi-Main/build
    fi

    echo " "
    cd ../../
}

if [ -n "$2" ] && [ "$2" = "clean" ]; then
    build Termi-Main clean executable
    build Termi-Commands clean library
    build Termi-GUI clean library
else
    build Termi-Main executable
    build Termi-Commands library
    build Termi-GUI library
fi

cd Termi-Main/build
cp ../termi.png .

LD_LIBRARY_PATH=. ./Termi-Main
cd ../
