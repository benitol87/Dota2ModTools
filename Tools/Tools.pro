TEMPLATE = lib

CONFIG += c++11

#TARGET = truc.dll ???
# Input
SOURCES += src/abilityparser.cpp src/objectelement.cpp src/pairelement.cpp src/stringelement.h
HEADERS += include/dll_include.h include/abilityparser.h include/objectelement.h include/pairelement.h include/stringelement.h include/valueelement.h

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += TOOLS_LIBRARY