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

g++ -std=c++17 -Werror -Wreorder -Wsign-compare -Waddress -Wcomment -Wformat -Wbool-compare -Wuninitialized -Wunknown-pragmas -Wunused-value -Wpointer-arith -Wcast-qual -Wno-missing-braces -Wunused-value  `wx-config --cxxflags --libs` -o build/QuickTodo.o -c src/QuickTodo.cpp
g++ -std=c++17 -Werror -Wreorder -Wsign-compare -Waddress -Wcomment -Wformat -Wbool-compare -Wuninitialized -Wunknown-pragmas -Wunused-value -Wpointer-arith -Wcast-qual -Wno-missing-braces -Wunused-value  `wx-config --cxxflags --libs` -o build/MainFrame.o -c src/MainFrame.cpp
g++ -std=c++17 -Werror -Wreorder -Wsign-compare -Waddress -Wcomment -Wformat -Wbool-compare -Wuninitialized -Wunknown-pragmas -Wunused-value -Wpointer-arith -Wcast-qual -Wno-missing-braces -Wunused-value  `wx-config --cxxflags --libs` -o build/MainApp.o -c src/MainApp.cpp
g++ -std=c++17 -Werror -Wreorder -Wsign-compare -Waddress -Wcomment -Wformat -Wbool-compare -Wuninitialized -Wunknown-pragmas -Wunused-value -Wpointer-arith -Wcast-qual -Wno-missing-braces -Wunused-value  -I./src./headers -o build/quick_list build/MainFrame.o build/MainApp.o build/QuickTodo.o `wx-config --cxxflags --libs`

./build/quick_list