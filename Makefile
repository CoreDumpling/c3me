CYGDRIVE := $(shell if uname | grep -iq cygwin; then echo '/cygdrive'; fi)

MINGW_DIR := $(CYGDRIVE)/c/MinGW

PATH := $(MINGW_DIR)/bin:$(PATH)

CFLAGS =
CC = gcc $(CFLAGS)

all: c3cinfo.exe datadump.exe mp.exe
	echo $(CYGDRIVE)
	cd gui && $(MAKE)

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
	cd gui && $(MAKE) clean

.PHONY: all clean
