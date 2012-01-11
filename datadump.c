/* Utility to dump contents of data structures */

#include "c3c.h"
#include <stdio.h>

#define PRINT_STR(data, field) \
        do { \
                printf(#data "+%04x (" #field "): %.*s\n", \
                       (int) &data.field - (int) &data, sizeof(data.field), \
                       data.field); \
        } while (0);
#define PRINT_FIELD(data, field, fmt) \
        do { \
                printf(#data "+%04x (" #field "): " fmt "\n", \
                       (int) &data.field - (int) &data, data.field); \
        } while (0);
#define PRINT_FIELD_BUF(data, field, fmt) \
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
    PRINT_FIELD_BUF(bic, no_idea_1, "%p");
    PRINT_FIELD(bic, biqFilenamePtr, "%p");
    PRINT_FIELD_BUF(bic, no_idea_2, "%p");
    PRINT_STR(bic, pathNoExt);
    PRINT_STR(bic, pathWithExt);
    PRINT_STR(bic, c3cPath);
    PRINT_STR(bic, ptwPath);
    PRINT_FIELD_BUF(bic, no_idea_3, "%p");
    PRINT_STR(bic, saveTmp);
    PRINT_STR(bic, no_idea_4);
    PRINT_FIELD_BUF(bic, no_idea_5, "%p");
    PRINT_FIELD(bic, nTechs, "%d");
    PRINT_FIELD(bic, nUnits, "%d");
    PRINT_FIELD(bic, nBuildings, "%d");
    PRINT_FIELD(bic, no_idea_6, "%d");
    PRINT_FIELD(bic, nCitizens, "%d");
    PRINT_FIELD(bic, no_idea_6b, "%d");
    PRINT_FIELD(bic, nCulturalOpinions, "%d");
    PRINT_FIELD(bic, nDifficultyLevels, "%d");
    PRINT_FIELD_BUF(bic, no_idea_6c, "%d");
    PRINT_FIELD(bic, nResources, "%d");
    PRINT_FIELD(bic, no_idea_7, "%d");
    PRINT_FIELD(bic, nPlayers, "%d");
    PRINT_FIELD_BUF(bic, no_idea_8, "%d");
    PRINT_STR(bic, description);
    PRINT_STR(bic, scenarioTitle);
    PRINT_FIELD(bic, no_idea_9, "%p");
    PRINT_FIELD(bic, buildingsPtr, "%p");
    PRINT_FIELD(bic, citizensPtr, "%p");
    PRINT_FIELD(bic, cityNamesPtr, "%p");
    PRINT_FIELD(bic, no_idea_10, "%p");
    PRINT_FIELD(bic, culturePtr, "%p");
    PRINT_FIELD(bic, difficultyPtr, "%p");
    PRINT_FIELD(bic, erasPtr, "%p");
    PRINT_FIELD(bic, espionagePtr, "%p");
    PRINT_FIELD(bic, experiencePtr, "%p");
    PRINT_FIELD_BUF(bic, no_idea_11, "%p");
    PRINT_FIELD(bic, no_idea_12_ptr, "%p");
    PRINT_FIELD(bic, no_idea_13_ptr, "%p");
    PRINT_FIELD_BUF(bic, no_idea_14, "%p");
    PRINT_FIELD(bic, autoPlaceCaptureUnits, "%d");
    PRINT_FIELD(bic, autoPlaceKingUnits, "%d");
    PRINT_FIELD(bic, autoPlaceVictoryLocations, "%d");
    PRINT_FIELD(bic, useDebugMode, "%d");
    PRINT_FIELD(bic, useTimeLimits, "%d");
    PRINT_FIELD(bic, baseTimeUnit, "%d");
    PRINT_FIELD(bic, startMonth, "%d");
    PRINT_FIELD(bic, startWeek, "%d");
    PRINT_FIELD(bic, startYear, "%d");
    PRINT_FIELD(bic, timeLimitMinutes, "%d");
    PRINT_FIELD(bic, timeLimitTurns, "%d");
    PRINT_FIELD_BUF(bic, timeScaleTurns, "%d");
    PRINT_FIELD_BUF(bic, timeScaleUnits, "%d");
    PRINT_FIELD(bic, victoryPointLimit, "%d");
    PRINT_FIELD(bic, cityEliminationCount, "%d");
    PRINT_FIELD(bic, cultureVictoryCity, "%d");
    PRINT_FIELD(bic, cultureVictoryCiv, "%d");
    PRINT_FIELD(bic, terrainForDomination, "%d");
    PRINT_FIELD(bic, populationForDomination, "%d");
    PRINT_FIELD(bic, wonderVP, "%d");
    PRINT_FIELD(bic, defeatUnitVP, "%d");
    PRINT_FIELD(bic, advanceVP, "%d");
    PRINT_FIELD(bic, cityConquestVP, "%d");
    PRINT_FIELD(bic, victoryPointLocationVP, "%d");
    PRINT_FIELD(bic, captureUnitVP, "%d");
    PRINT_FIELD(bic, captureUnitGold, "%d");
    PRINT_FIELD(bic, no_idea_15, "%d");
    PRINT_STR(bic, scenarioSearchFolders);
    PRINT_FIELD_BUF(bic, no_idea_16, "%p");
    PRINT_STR(bic, alliance1Name);
    PRINT_STR(bic, alliance2Name);
    PRINT_STR(bic, alliance3Name);
    PRINT_STR(bic, alliance4Name);
    PRINT_FIELD_BUF(bic, no_idea_17, "%p");
    PRINT_STR(bic, scenarioTitle2);
    PRINT_FIELD_BUF(bic, no_idea_18, "%p");
    PRINT_FIELD(bic, racesPtr, "%p");
    PRINT_FIELD(bic, resourcesPtr, "%p");
    PRINT_FIELD(bic, govtsPtr, "%p");
    PRINT_FIELD(bic, playersPtr, "%p");
    PRINT_FIELD(bic, unitsPtr, "%p");
    PRINT_FIELD(bic, menuArtPtr, "%p");
    PRINT_FIELD(bic, no_idea_19, "%p");
    PRINT_STR(bic, citySize1);
    PRINT_STR(bic, citySize2);
    PRINT_STR(bic, citySize3);
    PRINT_FIELD_BUF(bic, no_idea_20, "%p");
    PRINT_FIELD(bic, culturalLevelsPtr, "%p");
    PRINT_FIELD(bic, levelMultiplier, "%d");
    PRINT_FIELD(bic, nCulturalLevels, "%d");
    PRINT_FIELD(bic, borderFactor, "%d");
    PRINT_FIELD(bic, futureTechCost, "%d");
    PRINT_FIELD_BUF(bic, no_idea_21, "%p");
    PRINT_FIELD(bic, techsPtr, "%p");
    PRINT_FIELD(bic, workerJobsPtr, "%p");
    PRINT_FIELD(bic, terrainPtr, "%p");
    PRINT_FIELD(bic, no_idea_22_ptr, "%p");
    PRINT_FIELD(bic, worldSizesPtr, "%p");
    PRINT_FIELD(bic, flavorsPtrPtr, "%p");
    PRINT_FIELD(bic, screenWidthPixels, "%d");
    PRINT_FIELD(bic, screenHeightPixels, "%d");
    PRINT_FIELD(bic, no_idea_24, "%p");
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
    PRINT_FIELD_BUF(lead, no_idea_1, "%p");
    PRINT_FIELD(lead, id, "%d");
    PRINT_FIELD(lead, nationality, "%d");
    PRINT_FIELD_BUF(lead, no_idea_2, "%p");
    PRINT_FIELD(lead, capitalCityId, "%d");
    PRINT_FIELD_BUF(lead, no_idea_3, "%p");
    PRINT_FIELD(lead, posGold, "%d");
    PRINT_FIELD(lead, negGold, "%d");
    PRINT_FIELD_BUF(lead, no_idea_4, "%p");
    PRINT_FIELD(lead, govt, "%d");
    PRINT_FIELD_BUF(lead, no_idea_5, "%p");
    PRINT_FIELD(lead, beakers, "%d");
    PRINT_FIELD(lead, researchTech, "%d");
    PRINT_FIELD_BUF(lead, no_idea_6, "%p");
    PRINT_FIELD(lead, nUnits, "%d");
    PRINT_FIELD_BUF(lead, no_idea_7, "%p");
    PRINT_FIELD(lead, luxury, "%d");
    PRINT_FIELD(lead, science, "%d");
    PRINT_FIELD(lead, tax, "%d");
    PRINT_FIELD_BUF(lead, no_idea_8, "%p");
    PRINT_FIELD_BUF(lead, contacts, "%d");
    PRINT_FIELD_BUF(lead, no_idea_9, "%p");
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
	PRINT_FIELD(unit, no_idea_1, "%p");
	PRINT_FIELD(unit, id, "%d");
	PRINT_FIELD(unit, x, "%d");
	PRINT_FIELD(unit, y, "%d");
	PRINT_FIELD(unit, prevx, "%d");
	PRINT_FIELD(unit, prevy, "%d");
	PRINT_FIELD(unit, owner, "%d");
	PRINT_FIELD(unit, nationality, "%d");
	PRINT_FIELD(unit, no_idea_3, "%d");
	PRINT_FIELD(unit, type, "%d");
	PRINT_FIELD(unit, experience, "%d");
	PRINT_FIELD(unit, no_idea_4, "%d");
	PRINT_FIELD(unit, damage, "%d");
	PRINT_FIELD(unit, usedMovement, "%d");
	PRINT_FIELD(unit, no_idea_5, "%d");
	PRINT_FIELD(unit, workerAction, "%d");
	PRINT_FIELD_BUF(unit, no_idea_6, "%d");
	PRINT_FIELD(unit, fortified, "%d");
	PRINT_FIELD(unit, endTurn, "%d");
	PRINT_FIELD_BUF(unit, no_idea_7, "%d");
	PRINT_STR(unit, name);
	PRINT_FIELD_BUF(unit, no_idea_8, "%d");
	PRINT_FIELD_BUF(unit, no_idea_9, "%d");
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

    if (!FindC3C()) {
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
