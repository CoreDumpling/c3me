#include "c3c.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    /* bitmask for which players are human-controlled */
    uint32_t mask = 0;
    /* flag for whether or not multiplayer is enabled */
    char flag = 1;

    if (!WriteC3CMemory(MP_FLAG_ADDR, &flag, sizeof(char))) {
	fprintf(stderr, "Unable to activate multiplayer mode.\n");
	return 1;
    }

    int a;
    for (a = 1; a < argc; ++a) {
	int p = atoi(argv[a]);
	if (p < 32) {
	    mask |= 1 << p;
	} else {
	    printf("Invalid player: %d\n", p);
	}
    }

    if (!WriteC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t)))
	return 1;
    if (!ReadC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t)))
	return 1;

    printf("Current human players:");
    int p;
    for (p = 0; p < 32; ++p) {
	if (1 << p & mask) {
	    printf(" %d", p);
	}
    }
    printf("\n");

    return 0;
}
