CONFIG += c++11 console
CONFIG -= app_bundle

DEPENDPATH += . ../Tools
INCLUDEPATH += ../Tools/include
LIBS += -L../Tools -lTools

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp
