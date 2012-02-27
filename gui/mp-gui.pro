TEMPLATE = app
TARGET = mp-gui
DEPENDPATH += . ..
INCLUDEPATH += . ..
CONFIG += release
DESTDIR = .
QMAKE_LFLAGS = -static
LIBS += ../c3c.o

# Input
HEADERS += MPApp.h
SOURCES += mp-gui.cpp MPApp.cpp
