CFLAGS = -mno-cygwin
CC = gcc $(CFLAGS)

all: rules.exe datadump.exe

c3c.o: c3c.c c3c.h
	$(CC) -c c3c.c -o $@

rules.exe: rules.c c3c.o
	$(CC) $^ -o $@

datadump.exe: datadump.c c3c.o
	$(CC) $^ -o $@

clean:
	rm -f *.exe *.o *.stackdump

.PHONY: clean
