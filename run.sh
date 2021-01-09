#!/bin/bash
echo "Start Build Project"
rm -rf build/
mkdir build
cd build
cmake ..
make
echo "Project Build Success !"
echo 'Start Run SimpleDB'
./SimpleDB
# echo 'Start Analysis runing log'
# python analysis.py 
# echo 'All have Done !'