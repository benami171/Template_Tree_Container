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
    # Add any specific configurations for the tree build here
}

CONFIG(test): {
    TARGET = test
    SOURCES += test_main.cpp # Assuming you have a separate main for tests
    HEADERS += test_tree.hpp # Assuming you have additional headers for tests
    # Add any specific configurations for the test build here
}

# Custom run target for development convenience
run.target = run
run.commands = $$TARGET
QMAKE_EXTRA_TARGETS += run