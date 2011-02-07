// Utility to dump contents of data structures

#include "c3c.h"
#include <stdio.h>

#define PRINT_STR(data, field) \
        do { \
                printf(#data "+%04x (" #field "): %.*s\n", \
                       (int) &data.field - (int) &data, sizeof(data.field), \
                       data.field); \
        } while (0);
#define PRINT_HEX(data, field, fmt) \
        do { \
                printf(#data "+%04x (" #field "): " fmt "\n", \
                       (int) &data.field - (int) &data, data.field); \
        } while (0);
#define PRINT_HEX_BUF(data, field, fmt) \
        do { \
                int len = sizeof(data.field) / sizeof(uint32_t); \
                int i; \
                for (i = 0; i < len; ++i) { \
                        printf(#data "+%04x (" #field "[%d]): " fmt "\n", \
                               (int) &data.field[i] - (int) &data, i, \
                               data.field[i]); \
                } \
        } while (0);

int dump_bic()
{
	Bic bic;

	if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
		return 1;
	}

	PRINT_STR(bic, BIC);
	PRINT_HEX_BUF(bic, no_idea_1, "%p");
	PRINT_HEX(bic, biqFilenamePtr, "%p");
	PRINT_HEX_BUF(bic, no_idea_2, "%p");
	PRINT_STR(bic, pathNoExt);
	PRINT_STR(bic, pathWithExt);
	PRINT_STR(bic, c3cPath);
	PRINT_STR(bic, ptwPath);
	PRINT_HEX_BUF(bic, no_idea_3, "%p");
	PRINT_STR(bic, saveTmp);
	PRINT_STR(bic, no_idea_4);
	PRINT_HEX_BUF(bic, no_idea_5, "%p");
	PRINT_HEX(bic, nTechs, "%d");
	PRINT_HEX(bic, nUnits, "%d");
	PRINT_HEX(bic, nBuildings, "%d");
	PRINT_HEX(bic, no_idea_6, "%d");
	PRINT_HEX(bic, nCitizens, "%d");
	PRINT_HEX(bic, no_idea_6b, "%d");
	PRINT_HEX(bic, nCulturalOpinions, "%d");
	PRINT_HEX(bic, nDifficultyLevels, "%d");
	PRINT_HEX_BUF(bic, no_idea_6c, "%d");
	PRINT_HEX(bic, nResources, "%d");
	PRINT_HEX(bic, no_idea_7, "%d");
	PRINT_HEX(bic, nPlayers, "%d");
	PRINT_HEX_BUF(bic, no_idea_8, "%d");
	PRINT_STR(bic, description);
	PRINT_STR(bic, scenarioTitle);
	PRINT_HEX(bic, no_idea_9, "%p");
	PRINT_HEX(bic, buildingsPtr, "%p");
	PRINT_HEX(bic, citizensPtr, "%p");
	PRINT_HEX(bic, cityNamesPtr, "%p");
	PRINT_HEX(bic, no_idea_10, "%p");
	PRINT_HEX(bic, culturePtr, "%p");
	PRINT_HEX(bic, difficultyPtr, "%p");
	PRINT_HEX(bic, erasPtr, "%p");
	PRINT_HEX(bic, espionagePtr, "%p");
	PRINT_HEX(bic, experiencePtr, "%p");
	PRINT_HEX_BUF(bic, no_idea_11, "%p");
	PRINT_HEX(bic, no_idea_12_ptr, "%p");
	PRINT_HEX(bic, no_idea_13_ptr, "%p");
	PRINT_HEX_BUF(bic, no_idea_14, "%p");
	PRINT_HEX(bic, victoryPointLimit, "%d");
	PRINT_HEX(bic, cityEliminationCount, "%d");
	PRINT_HEX(bic, cultureVictoryCity, "%d");
	PRINT_HEX(bic, cultureVictoryCiv, "%d");
	PRINT_HEX(bic, terrainForDomination, "%d");
	PRINT_HEX(bic, populationForDomination, "%d");
	PRINT_HEX(bic, wonderVP, "%d");
	PRINT_HEX(bic, defeatUnitVP, "%d");
	PRINT_HEX(bic, advanceVP, "%d");
	PRINT_HEX(bic, cityConquestVP, "%d");
	PRINT_HEX(bic, victoryPointLocationVP, "%d");
	PRINT_HEX(bic, captureUnitVP, "%d");
	PRINT_HEX(bic, captureUnitGold, "%d");
	PRINT_HEX(bic, no_idea_15, "%d");
	PRINT_STR(bic, scenarioSearchFolders);
	PRINT_HEX_BUF(bic, no_idea_16, "%p");
	PRINT_STR(bic, alliance1Name);
	PRINT_STR(bic, alliance2Name);
	PRINT_STR(bic, alliance3Name);
	PRINT_STR(bic, alliance4Name);
	PRINT_HEX_BUF(bic, no_idea_17, "%p");
	PRINT_STR(bic, scenarioTitle2);
	PRINT_HEX_BUF(bic, no_idea_18, "%p");
	PRINT_HEX(bic, racesPtr, "%p");
	PRINT_HEX(bic, resourcesPtr, "%p");
	PRINT_HEX(bic, govtsPtr, "%p");
	PRINT_HEX(bic, playersPtr, "%p");
	PRINT_HEX(bic, unitsPtr, "%p");
	PRINT_HEX(bic, menuArtPtr, "%p");
	PRINT_HEX(bic, no_idea_19, "%p");
	PRINT_STR(bic, citySize1);
	PRINT_STR(bic, citySize2);
	PRINT_STR(bic, citySize3);
	PRINT_HEX_BUF(bic, no_idea_20, "%p");
	PRINT_HEX(bic, culturalLevelsPtr, "%p");
	PRINT_HEX(bic, levelMultiplier, "%d");
	PRINT_HEX(bic, nCulturalLevels, "%d");
	PRINT_HEX(bic, borderFactor, "%d");
	PRINT_HEX(bic, futureTechCost, "%d");
	PRINT_HEX_BUF(bic, no_idea_21, "%p");
	PRINT_HEX(bic, techsPtr, "%p");
	PRINT_HEX(bic, workerJobsPtr, "%p");
	PRINT_HEX(bic, terrainPtr, "%p");
	PRINT_HEX(bic, no_idea_22_ptr, "%p");
	PRINT_HEX(bic, worldSizesPtr, "%p");
	PRINT_HEX(bic, flavorsPtrPtr, "%p");
	PRINT_HEX(bic, screenWidthPixels, "%d");
	PRINT_HEX(bic, screenHeightPixels, "%d");
	PRINT_HEX(bic, no_idea_24, "%p");
	return 0;
}

int dump_lead(int leadId)
{
	uint32_t leadPtr;
	Leader lead;
	if (!ReadC3CMemory(LEADERS_BEGIN_ADDR + leadId * sizeof(Leader),
			   &lead, sizeof(Leader))) {
		return 1;
	}
	PRINT_STR(lead, LEAD);
	PRINT_HEX_BUF(lead, no_idea_1, "%p");
	PRINT_HEX(lead, id, "%d");
	PRINT_HEX(lead, nationality, "%d");
	PRINT_HEX_BUF(lead, no_idea_2, "%p");
	PRINT_HEX(lead, capitalCityId, "%d");
	PRINT_HEX_BUF(lead, no_idea_3, "%p");
	PRINT_HEX(lead, posGold, "%d");
	PRINT_HEX(lead, negGold, "%d");
	PRINT_HEX_BUF(lead, no_idea_4, "%p");
	PRINT_HEX(lead, govt, "%d");
	PRINT_HEX_BUF(lead, no_idea_5, "%p");
	PRINT_HEX(lead, beakers, "%d");
	PRINT_HEX(lead, researchTech, "%d");
	PRINT_HEX_BUF(lead, no_idea_6, "%p");
	PRINT_HEX(lead, nUnits, "%d");
	PRINT_HEX_BUF(lead, no_idea_7, "%p");
	PRINT_HEX(lead, luxury, "%d");
	PRINT_HEX(lead, science, "%d");
	PRINT_HEX(lead, tax, "%d");
	PRINT_HEX_BUF(lead, no_idea_8, "%p");
	PRINT_HEX_BUF(lead, contacts, "%d");
	PRINT_HEX_BUF(lead, no_idea_9, "%p");
	return 0;
}

int dump_unit(int unitId)
{
	uint32_t unitsPtr;
	uint32_t unitValid, unitValidPtr;
	uint32_t unitPtr, unitPtrPtr;
	if (!ReadC3CMemory(UNITS_BEGIN_ADDR, &unitsPtr, sizeof(uint32_t))) {
		return 1;
	}
	unitValidPtr = unitsPtr + unitId * 2 * sizeof(uint32_t);
	if (!ReadC3CMemory(unitValidPtr, &unitValid, sizeof(uint32_t))) {
		return 1;
	}
	unitPtrPtr = unitValidPtr + sizeof(uint32_t);
	if (unitValid != 0xffffffff) {
		fprintf(stderr, "Invalid unit id: %d\n", unitId);
		return 1;
	} else {
		Unit unit;
		if (!ReadC3CMemory(unitPtrPtr, &unitPtr, sizeof(uint32_t))) {
			return 1;
		}
		if (!unitPtr) {
			fprintf(stderr, "Error: NULL pointer\n");
			return 1;
		}
		if (!ReadC3CMemory(unitPtr, &unit, sizeof(Unit))) {
			return 1;
		}
		PRINT_HEX(unit, no_idea_1, "%p");
		PRINT_HEX(unit, id, "%d");
		PRINT_HEX(unit, x, "%d");
		PRINT_HEX(unit, y, "%d");
		PRINT_HEX(unit, prevx, "%d");
		PRINT_HEX(unit, prevy, "%d");
		PRINT_HEX(unit, owner, "%d");
		PRINT_HEX(unit, nationality, "%d");
		PRINT_HEX(unit, no_idea_3, "%d");
		PRINT_HEX(unit, type, "%d");
		PRINT_HEX(unit, experience, "%d");
		PRINT_HEX(unit, no_idea_4, "%d");
		PRINT_HEX(unit, damage, "%d");
		PRINT_HEX(unit, usedMovement, "%d");
		PRINT_HEX(unit, no_idea_5, "%d");
		PRINT_HEX(unit, workerAction, "%d");
		PRINT_HEX_BUF(unit, no_idea_6, "%d");
		PRINT_HEX(unit, fortified, "%d");
		PRINT_HEX(unit, endTurn, "%d");
		PRINT_HEX_BUF(unit, no_idea_7, "%d");
		PRINT_STR(unit, name);
		PRINT_HEX_BUF(unit, no_idea_8, "%d");
		PRINT_HEX_BUF(unit, no_idea_9, "%d");
	}
	return 0;
}

void print_usage()
{
	fprintf(stderr, "Usage: datadump <data-type> [<id>]\n");
	fprintf(stderr, "data-type may be:\n");
	fprintf(stderr, "\tbic\n");
	fprintf(stderr, "\tleader\n");
	fprintf(stderr, "\tunit\n");
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		print_usage();
		return 1;
	}

	if (!strcmp("bic", argv[1])) {
		return dump_bic();
	} else if (!strcmp("leader", argv[1])) {
		if (argc < 3) {
			fprintf(stderr, "Leader id required\n");
			print_usage();
			return 1;
		}
		return dump_lead(atoi(argv[2]));
	} else if (!strcmp("unit", argv[1])) {
		if (argc < 3) {
			fprintf(stderr, "Unit id required\n");
			print_usage();
			return 1;
		}
		return dump_unit(atoi(argv[2]));
	} else {
		fprintf(stderr, "Unrecognized option: %s\n", argv[1]);
		print_usage();
		return 1;
	}
}
