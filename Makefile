QT_DIR := /cygdrive/c/Qt/4.8.0
MINGW_DIR := /cygdrive/c/MinGW

PATH := ${QT_DIR}/bin:${MINGW_DIR}/bin:${PATH}

CFLAGS =
CC = gcc $(CFLAGS)

all: c3cinfo.exe datadump.exe mp.exe
	(cd gui && make)

c3c.o: c3c.c c3c.h
	$(CC) -c c3c.c -o $@

c3cinfo.exe: c3cinfo.c c3c.o
	$(CC) $^ -o $@

datadump.exe: datadump.c c3c.o
	$(CC) $^ -o $@

mp.exe: mp.c c3c.o
	$(CC) $^ -o $@

clean:
	rm -f *.exe *.o *.stackdump
	(cd gui && make clean)

.PHONY: clean
