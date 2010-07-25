all: rules.exe

c3c.o: c3c.c c3c.h
	gcc -c c3c.c -o $@

rules.exe: rules.c c3c.o
	gcc $^ -o $@

datadump.exe: datadump.c c3c.o
	gcc $^ -o $@

clean:
	rm -f *.exe *.o *.stackdump

.PHONY: clean
