#!/bin/bash

mkdir -p build

cd build

qmake6 ../GenAlgGUI.pro && make && ./GenAlgGUI