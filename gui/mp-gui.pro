TEMPLATE = app
TARGET = mp-gui
DEPENDPATH += . ..
INCLUDEPATH += . ..
CONFIG += release
DESTDIR = .
QMAKE_LFLAGS = -static
LIBS += ../c3c.o

# Input
SOURCES += mp-gui.cpp
