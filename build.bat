@echo off
cd build
premake5 clean
premake5 gmake
premake5 ecc
cd ..
mingw32-make