QT       += core gui widgets
TEMPLATE = app

HEADERS += node.hpp tree.hpp complex.hpp
CONFIG += c++11
CONFIG -= app_bundle

CONFIG(Prog): {
    TARGET = Prog
    SOURCES += main.cpp
}

CONFIG(Test): {
    TARGET = Test
    SOURCES += test.cpp 
    HEADERS += doctest.h
}

# Custom target to run the executable
tree.target = tree
tree.commands = ./Prog
tree.depends = Prog
test.target = test
test.commands = ./Test
test.depends = Test
QMAKE_EXTRA_TARGETS += tree test