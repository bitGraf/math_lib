#!/usr/bin/bash

if [[ "$1" == "no_colors" ]]; then
	S=''
	E=''
else
	S='\033[1;33m'
	E='\033[0m'
fi

# setup directory structure
mkdir -p lbuild
mkdir -p bin

# setup build variables
# generator="Unix Makefiles"
export CC=clang
export CXX=clang++
generator="Ninja"

echo -e "$S[Configuring]$E"
cmake -G "$generator" -S . -B lbuild -DCMAKE_BUILD_TYPE=Debug
echo -e "$S[Building]$E"
cmake --build lbuild
#echo "[Installing]"
#cmake --install lbuild
