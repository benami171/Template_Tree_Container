QT       += core gui widgets
TEMPLATE = app

# Common configuration
SOURCES += main.cpp
HEADERS += node.hpp tree.hpp complex.hpp
CONFIG += c++11
CONFIG -= app_bundle

# Custom configurations
CONFIG(tree): {
    TARGET = tree
    tree.commands = ./tree
}

CONFIG(test): {
    TARGET = test
    SOURCES += test_main.cpp # Assuming you have a separate main for tests
    HEADERS += test_tree.hpp # Assuming you have additional headers for tests
}