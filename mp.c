#include <stdio.h>
#include <stdlib.h>
#include "c3c.h"

int main(int argc, char **argv)
{
    /* bitmask for which players are human-controlled */
    uint32_t mask = 0;
    /* flag for whether or not multiplayer is enabled */
    char flag = 1;

    if (!FindC3C()) {
	return 1;
    }
    if (!WriteC3CMemory(MP_FLAG_ADDR, &flag, sizeof(char))) {
	fprintf(stderr, "Unable to activate multiplayer mode.\n");
	return 1;
    }

    if (argc > 1) {
	/* Set player ids from command line to human-controlled */
	int a;
	for (a = 1; a < argc; ++a) {
	    int p = atoi(argv[a]);
	    if (p < 32) {
		mask |= 1 << p;
	    } else {
		printf("Invalid player: %d\n", p);
	    }
	}
    } else {
	/* No command line arguments, enter interactive mode */

	/* First get current multiplayer settings */
	if (!ReadC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t))) {
	    fprintf(stderr, "Unable to verify multiplayer settings.\n");
	    return 1;
	}

	/* Read BIC data block */
	Bic bic;
	if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
	    fprintf(stderr, "Unable to read BIC data.\n");
	    return 1;
	}

	/* Read RACE data for proper names of each civ */
	uint32_t nRaces;
	if (!ReadC3CMemory(bic.racesPtr - sizeof(uint32_t), &nRaces,
			   sizeof(uint32_t))) {
	    fprintf(stderr, "Unable to read number of civilizations.\n");
	    return 1;
	}
	RaceRule *raceRules = (RaceRule *) malloc(nRaces * sizeof(RaceRule));
	if (!ReadC3CMemory(bic.racesPtr, raceRules,
			   nRaces * sizeof(RaceRule))) {
	    fprintf(stderr, "Unable to read RACE data.\n");
	    return 1;
	}

	/* Read LEAD data for civs in current game */
	Leader leaders[32];
	if (!ReadC3CMemory(LEADERS_BEGIN_ADDR, &leaders, sizeof(leaders))) {
	    fprintf(stderr, "Unable to read LEAD data.\n");
	    return 1;
	}

	while (1) {
	    /* Display list of players and whether they are human/AI */
	    int i, n, s;
	    printf("Civs in current game (* means human-controlled):\n");
	    for (i = 0; i < 32; ++i) {
		if (leaders[i].nationality == -1) {
		    /* invalid leader -- not actually in game */
		    break;
		}
		printf(" %s %2d) %s\n", (1 << i & mask) ? "*" : " ", i,
		       raceRules[leaders[i].nationality].civName);
	    }
	    /* Prompt user for civ ids to toggle between human/AI */
	    printf("Enter the number of the civ you wish to toggle\n"
		   "(* to make all human, = to make all AI, or ! if done): ");
	    n = scanf(" %d", &s);
	    if (n > 0) {
		if (s >= 0 && s < 32) {
		    mask ^= 1 << s;
		}
	    } else {
		char c = 0;
		n = scanf(" %c", &c);
		if (c == '*') {
		    mask = 0xffffffff;
		} else if (c == '=') {
		    mask = 0;
		} else if (c == '!') {
		    break;
		}
	    }
	}
    }

    /* Commit changes to C3C process */
    if (!WriteC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t))) {
	fprintf(stderr, "Unable to modify multiplayer settings.\n");
	return 1;
    }
    if (!ReadC3CMemory(PLAYER_MASK_ADDR, &mask, sizeof(uint32_t))) {
	fprintf(stderr, "Unable to verify multiplayer settings.\n");
	return 1;
    }

    /* Print summary of results after changes made */
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
