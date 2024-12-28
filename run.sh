#!/usr/bin/env bash
if [ ! -d build ]; then
    mkdir build
fi
if [ -d build ]; then
    rm -rf ./build
fi
mkdir build

main_frame="src/MainFrame.cpp src/MainFrame.hpp"
main_app="src/MainApp.cpp src/MainApp.hpp"
quick_todo="src/QuickTodo.cpp src/QuickTodo.hpp"

g++ $main_frame $main_app $quick_todo `wx-config --libs` `wx-config --cxxflags` -o build/quick_list
./build/quick_list