CFLAGS = -mno-cygwin
CC = gcc $(CFLAGS)

all: c3cinfo.exe datadump.exe findbic.exe

c3c.o: c3c.c c3c.h
	$(CC) -c c3c.c -o $@

c3cinfo.exe: c3cinfo.c c3c.o
	$(CC) $^ -o $@

datadump.exe: datadump.c c3c.o
	$(CC) $^ -o $@

findbic.exe: findbic.c c3c.o
	$(CC) $^ -o $@

clean:
	rm -f *.exe *.o *.stackdump

.PHONY: clean
