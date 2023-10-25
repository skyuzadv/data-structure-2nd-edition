@echo off
echo Compiling ...
g++ 04.josephus.cpp -std=c++11 -o test.exe
timeout 2
test.exe