// Utility to dump contents of data structures

#include "c3c.h"
#include <stdio.h>

#define PRINT_STR(data, field) \
        do { \
                printf(#data "+%04x (" #field "): %.*s\n", \
                       (int) &data.field - (int) &data, sizeof(data.field), \
                       data.field); \
        } while (0);
#define PRINT_DWORD(data, field, fmt) \
        do { \
                printf(#data "+%04x (" #field "): " fmt "\n", \
                       (int) &data.field - (int) &data, data.field); \
        } while (0);
#define PRINT_DWORD_BUF(data, field, fmt) \
        do { \
                int len = sizeof(data.field) / sizeof(DWORD); \
                int i; \
                for (i = 0; i < len; ++i) { \
                        printf(#data "+%04x (" #field "[%d]): " fmt "\n", \
                               (int) &data.field[i] - (int) &data, i, \
                               data.field[i]); \
                } \
        } while (0);

int dump_bic() {
        Bic bic;

        if (!ReadC3CMemory(BIC_ADDR, &bic, sizeof(Bic))) {
                return 1;
        }

        PRINT_STR(bic, BIC);
        PRINT_DWORD_BUF(bic, no_idea_1, "0x%08x");
        PRINT_DWORD(bic, biqFilenamePtr, "0x%08x");
        PRINT_DWORD_BUF(bic, no_idea_2, "0x%08x");
        PRINT_STR(bic, pathNoExt);
        PRINT_STR(bic, pathWithExt);
        PRINT_STR(bic, c3cPath);
        PRINT_STR(bic, ptwPath);
        PRINT_DWORD_BUF(bic, no_idea_3, "0x%08x");
        PRINT_STR(bic, saveTmp);
        PRINT_STR(bic, no_idea_4);
        PRINT_DWORD_BUF(bic, no_idea_5, "0x%08x");
        PRINT_DWORD(bic, nTechs, "%d");
        PRINT_DWORD(bic, nUnits, "%d");
        PRINT_DWORD(bic, nBuildings, "%d");
        PRINT_DWORD(bic, no_idea_6, "%d");
        PRINT_DWORD(bic, nCitizens, "%d");
        PRINT_DWORD(bic, no_idea_6b, "%d");
        PRINT_DWORD(bic, nCulturalOpinions, "%d");
        PRINT_DWORD(bic, nDifficultyLevels, "%d");
        PRINT_DWORD_BUF(bic, no_idea_6c, "%d");
        PRINT_DWORD(bic, nResources, "%d");
        PRINT_DWORD(bic, no_idea_7, "%d");
        PRINT_DWORD(bic, nPlayers, "%d");
        PRINT_DWORD_BUF(bic, no_idea_8, "%d");
        PRINT_STR(bic, description);
        PRINT_STR(bic, scenarioTitle);
        PRINT_DWORD(bic, no_idea_9, "0x%08x");
        PRINT_DWORD(bic, buildingsPtr, "0x%08x");
        PRINT_DWORD(bic, citizensPtr, "0x%08x");
        PRINT_DWORD(bic, cityNamesPtr, "0x%08x");
        PRINT_DWORD(bic, no_idea_10, "0x%08x");
        PRINT_DWORD(bic, culturePtr, "0x%08x");
        PRINT_DWORD(bic, difficultyPtr, "0x%08x");
        PRINT_DWORD(bic, erasPtr, "0x%08x");
        PRINT_DWORD(bic, espionagePtr, "0x%08x");
        PRINT_DWORD(bic, experiencePtr, "0x%08x");
        PRINT_DWORD_BUF(bic, no_idea_11, "0x%08x");
        PRINT_DWORD(bic, no_idea_12_ptr, "0x%08x");
        PRINT_DWORD(bic, no_idea_13_ptr, "0x%08x");
        PRINT_DWORD_BUF(bic, no_idea_14, "0x%08x");
        PRINT_DWORD(bic, victoryPointLimit, "%d");
        PRINT_DWORD(bic, cityEliminationCount, "%d");
        PRINT_DWORD(bic, cultureVictoryCity, "%d");
        PRINT_DWORD(bic, cultureVictoryCiv, "%d");
        PRINT_DWORD(bic, terrainForDomination, "%d");
        PRINT_DWORD(bic, populationForDomination, "%d");
        PRINT_DWORD(bic, wonderVP, "%d");
        PRINT_DWORD(bic, defeatUnitVP, "%d");
        PRINT_DWORD(bic, advanceVP, "%d");
        PRINT_DWORD(bic, cityConquestVP, "%d");
        PRINT_DWORD(bic, victoryPointLocationVP, "%d");
        PRINT_DWORD(bic, captureUnitVP, "%d");
        PRINT_DWORD(bic, captureUnitGold, "%d");
        PRINT_DWORD(bic, no_idea_15, "%d");
        PRINT_STR(bic, scenarioSearchFolders);
        PRINT_DWORD_BUF(bic, no_idea_16, "0x%08x");
        PRINT_STR(bic, alliance1Name);
        PRINT_STR(bic, alliance2Name);
        PRINT_STR(bic, alliance3Name);
        PRINT_STR(bic, alliance4Name);
        PRINT_DWORD_BUF(bic, no_idea_17, "0x%08x");
        PRINT_STR(bic, scenarioTitle2);
        PRINT_DWORD_BUF(bic, no_idea_18, "0x%08x");
        PRINT_DWORD(bic, racesPtr, "0x%08x");
        PRINT_DWORD(bic, resourcesPtr, "0x%08x");
        PRINT_DWORD(bic, govtsPtr, "0x%08x");
        PRINT_DWORD(bic, playersPtr, "0x%08x");
        PRINT_DWORD(bic, unitsPtr, "0x%08x");
        PRINT_DWORD(bic, menuArtPtr, "0x%08x");
        PRINT_DWORD(bic, no_idea_19, "0x%08x");
        PRINT_STR(bic, citySize1);
        PRINT_STR(bic, citySize2);
        PRINT_STR(bic, citySize3);
        PRINT_DWORD_BUF(bic, no_idea_20, "0x%08x");
        PRINT_DWORD(bic, culturalLevelsPtr, "0x%08x");
        PRINT_DWORD(bic, levelMultiplier, "%d");
        PRINT_DWORD(bic, nCulturalLevels, "%d");
        PRINT_DWORD(bic, borderFactor, "%d");
        PRINT_DWORD(bic, futureTechCost, "%d");
        PRINT_DWORD_BUF(bic, no_idea_21, "0x%08x");
        PRINT_DWORD(bic, techsPtr, "0x%08x");
        PRINT_DWORD(bic, workerJobsPtr, "0x%08x");
        PRINT_DWORD(bic, terrainPtr, "0x%08x");
        PRINT_DWORD(bic, no_idea_22_ptr, "0x%08x");
        PRINT_DWORD(bic, worldSizesPtr, "0x%08x");
        PRINT_DWORD(bic, flavorsPtrPtr, "0x%08x");
        PRINT_DWORD(bic, screenWidthPixels, "%d");
        PRINT_DWORD(bic, screenHeightPixels, "%d");
        PRINT_DWORD(bic, no_idea_24, "0x%08x");
        return 0;
}

int dump_lead(int leadId) {
        DWORD leadPtr;
        Leader lead;
        if (!ReadC3CMemory(LEADERS_BEGIN_ADDR + leadId * sizeof(Leader),
                           &lead, sizeof(Leader))) {
                return 1;
        }
        PRINT_STR(lead, LEAD);
        PRINT_DWORD_BUF(lead, no_idea_1, "0x%08x");
        PRINT_DWORD(lead, id, "%d");
        PRINT_DWORD(lead, nationality, "%d");
        PRINT_DWORD_BUF(lead, no_idea_2, "0x%08x");
        PRINT_DWORD(lead, capitalCityId, "%d");
        PRINT_DWORD_BUF(lead, no_idea_3, "0x%08x");
        PRINT_DWORD(lead, posGold, "%d");
        PRINT_DWORD(lead, negGold, "%d");
        PRINT_DWORD_BUF(lead, no_idea_4, "0x%08x");
        PRINT_DWORD(lead, govt, "%d");
        PRINT_DWORD_BUF(lead, no_idea_5, "0x%08x");
        PRINT_DWORD(lead, beakers, "%d");
        PRINT_DWORD(lead, researchTech, "%d");
        PRINT_DWORD_BUF(lead, no_idea_6, "0x%08x");
        PRINT_DWORD(lead, nUnits, "%d");
        PRINT_DWORD_BUF(lead, no_idea_7, "0x%08x");
        PRINT_DWORD(lead, luxury, "%d");
        PRINT_DWORD(lead, science, "%d");
        PRINT_DWORD(lead, tax, "%d");
        PRINT_DWORD_BUF(lead, no_idea_8, "0x%08x");
        PRINT_DWORD_BUF(lead, contacts, "%d");
        PRINT_DWORD_BUF(lead, no_idea_9, "0x%08x");
        return 0;
}

int dump_unit(int unitId) {
        DWORD unitsPtr;
        DWORD unitValid, unitValidPtr;
        DWORD unitPtr, unitPtrPtr;
        if (!ReadC3CMemory(UNITS_BEGIN_ADDR, &unitsPtr, sizeof(DWORD))) {
                return 1;
        }
        unitValidPtr = unitsPtr + unitId * 2 * sizeof(DWORD);
        if (!ReadC3CMemory(unitValidPtr, &unitValid, sizeof(DWORD))) {
                return 1;
        }
        unitPtrPtr = unitValidPtr + sizeof(DWORD);
        if (unitValid != 0xffffffff) {
                fprintf(stderr, "Invalid unit id: %d\n", unitId);
                return 1;
        } else {
                Unit unit;
                if (!ReadC3CMemory(unitPtrPtr, &unitPtr, sizeof(DWORD))) {
                        return 1;
                }
                if (!unitPtr) {
                        fprintf(stderr, "Error: NULL pointer\n");
                        return 1;
                }
                if (!ReadC3CMemory(unitPtr, &unit, sizeof(Unit))) {
                        return 1;
                }
                PRINT_DWORD(unit, no_idea_1, "0x%08x");
                PRINT_DWORD(unit, id, "%d");
                PRINT_DWORD(unit, x, "%d");
                PRINT_DWORD(unit, y, "%d");
                PRINT_DWORD(unit, prevx, "%d");
                PRINT_DWORD(unit, prevy, "%d");
                PRINT_DWORD(unit, owner, "%d");
                PRINT_DWORD(unit, nationality, "%d");
                PRINT_DWORD(unit, no_idea_3, "%d");
                PRINT_DWORD(unit, type, "%d");
                PRINT_DWORD(unit, experience, "%d");
                PRINT_DWORD(unit, no_idea_4, "%d");
                PRINT_DWORD(unit, damage, "%d");
                PRINT_DWORD(unit, usedMovement, "%d");
                PRINT_DWORD(unit, no_idea_5, "%d");
                PRINT_DWORD(unit, workerAction, "%d");
                PRINT_DWORD_BUF(unit, no_idea_6, "%d");
                PRINT_DWORD(unit, fortified, "%d");
                PRINT_DWORD(unit, endTurn, "%d");
                PRINT_DWORD_BUF(unit, no_idea_7, "%d");
                PRINT_STR(unit, name);
                PRINT_DWORD_BUF(unit, no_idea_8, "%d");
                PRINT_DWORD_BUF(unit, no_idea_9, "%d");
        }
        return 0;
}

void print_usage() {
        fprintf(stderr, "Usage: datadump <data-type> [<id>]\n");
        fprintf(stderr, "data-type may be:\n");
        fprintf(stderr, "\tbic\n");
        fprintf(stderr, "\tleader\n");
        fprintf(stderr, "\tunit\n");
}

int main(int argc, char** argv) {
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
