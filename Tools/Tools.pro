TEMPLATE = lib

CONFIG += c++11

INCLUDEPATH += ./include

TARGET = ../../Tools/Tools
TARGET_EXT = .dll
# Input
SOURCES += src/abilityparser.cpp src/objectelement.cpp src/pairelement.cpp src/stringelement.cpp
HEADERS += include/dll_include.h include/abilityparser.h include/objectelement.h include/pairelement.h include/stringelement.h include/valueelement.h

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += TOOLS_LIBRARY
