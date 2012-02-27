QT_DIR := /cygdrive/c/Qt/4.8.0
MINGW_DIR := /cygdrive/c/MinGW

QT_LIBS = mingwm10.dll QtCore4.dll QtGui4.dll
MINGW_LIBS = libgcc_s_dw2-1.dll

PATH := ${QT_DIR}/bin:${MINGW_DIR}/bin:${PATH}

all:
	qmake -o Makefile.qt
	mingw32-make -f Makefile.qt
	(cd ${QT_DIR}/bin; cp $(QT_LIBS) ${PWD}/release)
	(cd ${MINGW_DIR}/bin; cp $(MINGW_LIBS) ${PWD}/release)

clean:
	qmake -o Makefile.qt
	mingw32-make -f Makefile.qt clean
	rm -rf debug release
	rm Makefile.qt*
