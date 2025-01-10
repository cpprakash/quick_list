COMPILER=g++
COMPILER_VERSION=-std=c++17

COMPILER_OPTIONS= -Werror -Wreorder -Wsign-compare -Waddress -Wcomment -Wformat -Wbool-compare -Wuninitialized -Wunknown-pragmas -Wunused-value -Wpointer-arith -Wcast-qual -Wno-missing-braces -Wunused-value #-Wall
COMPILER_INCLUDES=-I./src./headers
WX_WIDGET=`wx-config --cxxflags --libs`


APP=quick_list


PROJECT=$(COMPILER) $(COMPILER_VERSION) $(COMPILER_OPTIONS) $(COMPILER_INCLUDES) -o build/quick_list

quick_list:QuickTodo.o MainFrame.o MainApp.o 
	$(PROJECT) build/MainFrame.o build/MainApp.o build/QuickTodo.o $(WX_WIDGET)

QuickTodo.o: src/QuickTodo.cpp headers/QuickTodo.hpp
	$(COMPILER) $(WX_WIDGET) -o build/QuickTodo.o -c src/QuickTodo.cpp

MainFrame.o: src/MainFrame.cpp headers/MainFrame.hpp
	$(COMPILER) $(COMPILER_VERSION) $(COMPILER_OPTIONS) $(WX_WIDGET) -o build/MainFrame.o -c src/MainFrame.cpp

MainApp.o: src/MainApp.cpp headers/MainApp.hpp
	$(COMPILER) $(COMPILER_VERSION) $(COMPILER_OPTIONS) $(WX_WIDGET) -o build/MainApp.o -c src/MainApp.cpp


