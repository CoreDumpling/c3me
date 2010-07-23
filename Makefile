RULES_EXE=rules.exe

all: $(RULES_EXE)

c3c.o: c3c.c c3c.h
	gcc -c c3c.c -o $@

rules.o: rules.c c3c.h
	gcc -c rules.c -o $@

$(RULES_EXE): rules.o c3c.o
	gcc $^ -o $@

bicdump.exe: bicdump.c c3c.o
	gcc $^ -o $@

clean:
	rm -f *.exe *.o *.stackdump
