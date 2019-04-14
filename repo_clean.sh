#!/bin/bash

cd Version-1
make clean

cd ..

cd Version-2
make clean


cd ..

rm -rf Random/*.out
rm -rf Random/*.elf
rm -rf Random/*.o

cd ..

exit
