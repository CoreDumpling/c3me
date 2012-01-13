#include "c3c.h"

int main(int argc, char **argv)
{
    Bic bic;
    int i;

    if (!FindC3C()) {
	printf("-- Press any key to exit --\n");
	getch();
	return 1;
    }

    int addr = 0x00900000;
    char BIC[4];
    while (addr < 0x01000000) {
	ReadC3CMemory(addr, BIC, 4);
	if (!strncmp("BIC ", BIC, 4)) {
	    printf("BIC found at: %p\n", addr);
	    printf("-- Press any key to exit --\n");
	    getch();
	    return 0;
	}
	addr += 4;
    }

    printf("Unable to find BIC\n");
    printf("-- Press any key to exit --\n");
    getch();
    return 1;
}
